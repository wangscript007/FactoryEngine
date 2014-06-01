
#include <Geometry/Triangle.h>
#include <Processing/FaceTraversal.h>
#include <Graph/PointNode.h>
#include <Graph/Edge.h>
#include <Graph/FaceNode.h>

namespace ftr {
    
bool FaceTraversal::IsSameFace(const Result& resultA, const Result& resultB)
{
    bool result = false;
    if (resultA.edgesVector[1] == resultB.edgesVector[resultB.edgesVector.size() - 1]->twin()) {
        result = true;
    }
    return result;
}
    
void FaceTraversal::Reverse(Result& result)
{
    std::vector<Edge*>& edgesVector = result.edgesVector;
    size_t size = edgesVector.size();
    for (int i = 0; i < size; ++i) {
        edgesVector[i] = edgesVector[i]->twin();
    }
    std::reverse(edgesVector.begin(),edgesVector.end());
}
    
FaceTraversal::~FaceTraversal()
{
    FT_DELETE(mPlane);
}
    
    
FaceTraversal::FaceTraversal(Edge& startEdge)
    : mStartEdge(&startEdge),
    mPlane(NULL),
    mIgnoreResult(NULL),
    mTargetNode(startEdge.originNode())
{
    
}

void FaceTraversal::Find(Result& result, Result* ignoreResult)
{
    mResult = &result;
    mIgnoreResult = ignoreResult;
    std::vector<Edge*>& edgesVector = mResult->edgesVector;
    
    FT_DELETE(mPlane);
    
    std::cout
    << "----------------------------------" << std::endl
    << "Find route from " << mStartEdge->targetNode()->mName
    << " to "<<  mStartEdge->originNode()->mName << std::endl;
    
    edgesVector.clear();
    edgesVector.push_back(mStartEdge);
    
    Find(mStartEdge->twin());
    
    mResult->hasUsedEdges = false;
    if (edgesVector.size() < 3)
    {
        edgesVector.clear();
    }
    else {
        for(int i = 0; i < edgesVector.size(); ++i) {
            Edge* edge = edgesVector[i];
            if (!edge->IsFree()) {
                mResult->hasUsedEdges = true;
                break;
            }
            
        }
        
        
        std::cout << "FOUND: ";
        for(int i = 0; i < edgesVector.size(); ++i) {
            std::cout << edgesVector[i]->Name() << " ";
        }
        std::cout << std::endl;
    }
}
    
bool FaceTraversal::Find(ftr::Edge *startEdge)
{
    std::vector<Edge*>& edgesVector = mResult->edgesVector;
    
    assert(edgesVector.size() >= 1); // must contain initial edge
    assert(edgesVector.size() < 1000);
    
    PointNode* originNode = startEdge->originNode();
    
    for(PointNode::Iterator i = originNode->Begin(); i != originNode->End(); ++i)
    {
        ftr::Edge* iEdge = *i;
        if (iEdge != edgesVector.back()->twin())
        {
            if (iEdge->targetNode() == mTargetNode)
            {
                if(PathContainsNode(edgesVector, *iEdge->targetNode())) {
                    return false;
                } else {
                    edgesVector.push_back(iEdge);
                    if (mIgnoreResult) {
                        if (IsSameFace(*mResult, *mIgnoreResult)) {
                            edgesVector.pop_back();
                            return false;
                        } else {
                            return true;
                        }
                        
                    }
                    return true;
                }
            }
            else if (iEdge->next() && !PathContainsNode(edgesVector, *iEdge->targetNode()))
            {
                if (edgesVector.size() > 0) {
                    
                    if (edgesVector.size() > 1 && !mPlane) CreatePlane();
                    else FT_DELETE(mPlane);
                    
                    if ( !mPlane || (mPlane && mPlane->PlaneContains(iEdge->target())) )
                    {
                        edgesVector.push_back(iEdge);
                        if ( Find(iEdge->next()) ) return true;
                        else edgesVector.pop_back();
                    }
                }
                else FT_DELETE(mPlane);
            }
        }
    }
    return false;
}
    
bool FaceTraversal::PathContainsNode(const std::vector<Edge*>& edges, const PointNode& pointNode)
{
    for (int i = 0; i < edges.size(); ++i) {
        Edge* edge = edges[i];
        if (edge->targetNode() == &pointNode) {
            return true;
        }
    }
    return false;
}
    
    
void FaceTraversal::PrintEdgesRoute() const
{
    for (auto it = mResult->edgesVector.begin(); it != mResult->edgesVector.end(); ++it) {
        std::cout << (*it)->Name() << " - ";
    }
    std::cout << std::endl;
}
    
void FaceTraversal::CreatePlane()
{
    assert(!mPlane);
    std::vector<Edge*>& edgesVector = mResult->edgesVector;
    assert(edgesVector.size() > 1);
    size_t size = edgesVector.size();
    Edge* e1 = edgesVector[size-2];
    Edge* e2 = edgesVector[size-1];
    
    glm::vec3 p1 = e1->origin();
    glm::vec3 p2 = e1->target();
    glm::vec3 p3 = e2->target();
    
    if (Triangle::IsInOneLine(p1, p2, p3)) {
        std::cout << "Points are in one line";
    } else {
        mPlane = new Triangle(e1->origin(), e1->target(), e2->target());
        //std::cout << "Created Triangle: " << mPlane->Description();
    }
}
    
}

