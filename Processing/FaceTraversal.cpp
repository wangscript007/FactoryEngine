

#include <Processing/FaceTraversal.h>
#include <Graph/Vertex.h>
#include <Graph/Edge.h>
#include <Geometry/Triangle.h>
#include <Geometry.h>
#include <Geometry/Polygon.h>

namespace ftr {
    
void FaceTraversal::EdgesConnectingVertexes(std::vector<Edge*>& edges,
                                            const std::vector<Vertex*>& vertexes)
{
    for (int i = 0; i < vertexes.size()-1; i++) {
        Edge* edge = vertexes[i]->EdgeTo(*vertexes[i+1]);
        assert(edge);
        edges.push_back(edge);
    }
    Edge* edge = vertexes.front()->EdgeTo(*vertexes.back());
    assert(edge);
    edges.push_back(edge);
}
    

    
    
#pragma mark - Instance

FaceTraversal::FaceTraversal(Vertex& vertex)
    :mVertex(vertex)
    ,mResult(NULL)
    ,mPlane(NULL)
{
    
}
    
void FaceTraversal::Find(Result& result)
{
    mResult = &result;
    mResult->mEdges.clear();
    mVertexes.clear();
    mPlane = NULL;
    
    AppendResult(mVertex);
    Find(mVertex);

    result.mVertexes = mVertexes;
    if(mVertexes.size() < 3) {
        mVertexes.clear();
    } else {
        FaceTraversal::EdgesConnectingVertexes(mResult->mEdges, mVertexes);
        //std::cout << Description(mResult) << "\n";
    }
}
 
bool FaceTraversal::Find(Vertex& current)
{
    std::vector<Vertex*> neighbours;
    UpdatePlane();
    if (mPlane) {
        current.CWNeighboursForNeighbour(neighbours, *Prev(), *mPlane);
    } else {
        current.Neighbours(neighbours);
        if (Prev()) {
            current.CWNeighboursForNeighbour(neighbours, *Prev());
        } else {
            current.Neighbours(neighbours);
        }
        
    }
    
    for (Vertex* vertex : neighbours) {
        Edge* edge = current.EdgeTo(*vertex);
        //std::cout << Description() << vertex->mName << " " << edge->Description() << "\n" ;
        /* Conditions
        * Must not be already in result pathvertex
        */
        if (Prev() != vertex
            && !edge->IsFull()
            && !IsInResultPath(*vertex)
            && !(mPlane && edge->Face(current, *vertex, *mPlane)) )
        {
            /* End condition
            * Equals to initial vertex
            */
            if (&mVertex == vertex) {
                Polygon polygon;
                for (Vertex* ver : mVertexes) {
                    polygon.AddPoint(ver->mOrigin);
                }
                return !polygon.IsCW();
            } else {
                AppendResult(*vertex);
                if (Find(*vertex)) return true;
                else mVertexes.pop_back();
            }
        }
    }
    return false;
}
    
    
void FaceTraversal::AppendResult(Vertex& vertex)
{
    mVertexes.push_back(&vertex);
}
    
#pragma mark - Conditions checking
    
Vertex* FaceTraversal::Prev() const
{
    if (mVertexes.size() > 1) {
        return *(mVertexes.end()-2);
    }
    return NULL;
}
    
bool FaceTraversal::IsInPlane(const Vertex& vertex)
{
    UpdatePlane();
    if (mPlane) {
        return mPlane->PlaneContains(vertex.mOrigin);
    }
    return true;
}
    
void FaceTraversal::UpdatePlane()
{
    if (mVertexes.size() < 3) {
        FT_DELETE(mPlane);
    }
    else if (mVertexes.size() > 2 && !mPlane) {
        size_t size = mVertexes.size();
        glm::vec3 p1 = mVertexes[size-3]->mOrigin;
        glm::vec3 p2 = mVertexes[size-2]->mOrigin;
        glm::vec3 p3 = mVertexes[size-1]->mOrigin;
        
        if (Triangle::IsInOneLine(p1, p2, p3)) {
            //std::cout << "Points are in one line";
        } else {
            mPlane = new Triangle(p1, p2, p3);
        }
    }
}

    
bool FaceTraversal::IsInResultPath(const Vertex& vertex) const
{
    return std::find(mVertexes.begin()+1, mVertexes.end(), &vertex) != mVertexes.end();
}
    
bool FaceTraversal::ContainsFace() const
{
    if (mVertexes.size() < 3) return false;
    
    std::vector<Edge*> edges;
    FaceTraversal::EdgesConnectingVertexes(edges, mVertexes);
    assert(edges.size() > 1);
    Edge* edge = edges.front();
    
    bool contains = false;
    for (auto& face : edge->mFaces) {
        contains = true;
        for (auto& edge : edges) {
            if (!edge->ContainsFace(*face)) {
                contains = false;
                break;
            }
        }
        if (contains) {
            return true;
        }
    }
    return contains;
}
    
#pragma mark - Plane
    
std::string FaceTraversal::Description() const
{
    std::stringstream ss;
    for (auto &vertex : mVertexes) {
        ss << vertex->mName << "-";
    }
    return ss.str();
}
    
std::string FaceTraversal::Description(Result* result) const
{
    assert(result);
    std::stringstream ss;
    for (auto &edge : result->mEdges) {
        ss << edge->Description() << " - ";
    }
    return ss.str();
}
        
}

