

#include <Processing/FaceTraversal.h>
#include <Graph/Vertex.h>
#include <Graph/Edge.h>
#include <Geometry/Triangle.h>

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
    for (auto &edge : current.mEdges) {
        Vertex* vertex = edge->OtherEnd(current);
        //std::cout << Description() << vertex->mName << " " << edge->Description() << "\n" ;
        /* Conditions
        * Must not be already in result pathvertex
        * Must be in same plane as previous vertexes
        * Must be not visited before?
        */
        if (!IsPrev(*vertex)
            && !edge->IsFull()
            && !IsInResultPath(*vertex)
            && !IsVisited(*vertex)
            && IsInPlane(*vertex))
        {
            /* End condition
            * Equals to initial vertex
            */
            if (&mVertex == vertex) {
                return true;
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
    
bool FaceTraversal::IsPrev(const Vertex& vertex) const
{
    auto &vertexes = mVertexes;
    if (vertexes.size() > 1) {
        Vertex* prev = *(vertexes.end()-2);
        return prev == &vertex;
    }
    return false;
}
    
bool FaceTraversal::IsInPlane(const Vertex& vertex)
{
    if (mVertexes.size() < 3) {
        FT_DELETE(mPlane);
    }
    if (mVertexes.size() > 2 && !mPlane) {
        CreatePlane();
    }
    if (mPlane) {
        return mPlane->PlaneContains(vertex.mOrigin);
    }
    return true;
}
    
void FaceTraversal::CreatePlane()
{
    assert(!mPlane);
    assert(mVertexes.size() > 2);
    size_t size = mVertexes.size();
    glm::vec3 p1 = mVertexes[size-3]->mOrigin;
    glm::vec3 p2 = mVertexes[size-2]->mOrigin;
    glm::vec3 p3 = mVertexes[size-1]->mOrigin;
    
    if (Triangle::IsInOneLine(p1, p2, p3)) {
        std::cout << "Points are in one line";
    } else {
        mPlane = new Triangle(p1, p2, p3);
    }
}

    
bool FaceTraversal::IsInResultPath(const Vertex& vertex) const
{
    auto &vertexes = mVertexes;
    return std::find(vertexes.begin()+1, vertexes.end(), &vertex) != vertexes.end();
}
    
bool FaceTraversal::IsVisited(const Vertex& vertex) const
{
    return false;
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

