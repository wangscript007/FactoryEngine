
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
    result.hasUsedEdges = AnyUsedEdge(result) != NULL;
}
    
Edge* FaceTraversal::AnyUsedEdge(const Result& result)
{
    for(int i = 0; i < result.edgesVector.size(); ++i) {
        Edge* edge = result.edgesVector[i];
        if (!edge->IsFree()) {
            return edge;
        }
    }
    return NULL;
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
    
//    std::cout
//    << "----------------------------------" << std::endl
//    << "Find route from " << mStartEdge->targetNode()->mName
//    << " to "<<  mStartEdge->originNode()->mName << std::endl;
    
    edgesVector.clear();
    edgesVector.push_back(mStartEdge);
    
    Find(mStartEdge->twin());
    
    mResult->hasUsedEdges = false;
    if (!mResult->FoundFace()) {
        mResult->Clear();
    }
    else {
        mResult->hasUsedEdges = AnyUsedEdge(*mResult) != NULL;
        
//        std::cout << "FOUND: ";
//        for(int i = 0; i < edgesVector.size(); ++i) {
//            std::cout << edgesVector[i]->Name() << " ";
//        }
//        std::cout << std::endl;
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
        ftr::Edge* edge = *i;
        
        if (IsNotTraversingBackwards(*edge)) {
            if (!PathContainsNode(*edge->targetNode())) {
                if (IsSamePlane(*edge)) {
                    
                    if (edge->targetNode() == mTargetNode) {
                        edgesVector.push_back(edge);
                        if (mIgnoreResult && IsSameFace(*mResult, *mIgnoreResult)) {
                            edgesVector.pop_back();
                            return false;
                        }
                        return true;
                    }
                    
                    else if (edge->next())
                    {
                        edgesVector.push_back(edge);
                        if ( Find(edge->next()) ) return true;
                        else edgesVector.pop_back();
                    }
                }
            }
        }
    }
    return false;
}
    
bool FaceTraversal::IsNotTraversingBackwards(const ftr::Edge& edge) const
{
    const std::vector<Edge*>& edgesVector = mResult->edgesVector;
    return &edge != edgesVector.back()->twin();
}
    
bool FaceTraversal::IsSamePlane(const ftr::Edge& edge)
{
    std::vector<Edge*>& edgesVector = mResult->edgesVector;
    if (edgesVector.size() < 2) {
        FT_DELETE(mPlane);
    }
    if (edgesVector.size() > 1 && !mPlane) {
        CreatePlane();
    }
    if (mPlane) {
        return mPlane->PlaneContains(edge.target());
    }
    return true;
}
    
bool FaceTraversal::PathContainsNode(const PointNode& pointNode)
{
    const std::vector<Edge*>& edges = mResult->edgesVector;
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

