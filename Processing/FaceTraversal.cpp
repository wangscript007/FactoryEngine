
#include <Geometry/Triangle.h>
#include <Processing/FaceTraversal.h>
#include <Model/PointNode.h>
#include <Model/Edge.h>
#include <Model/FaceNode.h>

namespace ftr {
    
bool FaceTraversal::IsSameFace(const Result& resultA, const Result& resultB)
{
    bool result = false;
    if (resultA.edgesVector[1] == resultB.edgesVector[resultB.edgesVector.size() - 1]->twin()) {
        result = true;
    }
    return result;
}
    
FaceTraversal::~FaceTraversal()
{
    FT_DELETE(mTriangle);
}
    
    
FaceTraversal::FaceTraversal(Edge& startEdge)
    : mStartEdge(&startEdge),
    mTriangle(NULL),
    mTargetNode(startEdge.originNode())
{
    
}

void FaceTraversal::Find(Result& result)
{
    mResult = &result;
    std::vector<Edge*>& edgesVector = mResult->edgesVector;
    if (mTriangle) {
        FT_DELETE(mTriangle);
    }
    
    std::cout
    << "----------------------------------" << std::endl
    << "Find route from " << mStartEdge->targetNode()->mName
    << " to "<<  mStartEdge->originNode()->mName << std::endl;
    edgesVector.clear();
    edgesVector.push_back(mStartEdge);
    
    Find(mStartEdge->twin());
    
    mResult->hasUsedEdges = false;
    if (edgesVector.size() < 3) {
        edgesVector.clear();
    } else {
        
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
    
    //std::cout << "Checking " << startEdge->Name() << " size: " << edgesVector.size() << std::endl;
    PointNode* originNode = startEdge->originNode();
    
    assert(edgesVector.size() < 20); // too far for simple tests
    
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
                    return true;
                }
            }
            else if (iEdge->next() && !PathContainsNode(edgesVector, *iEdge->targetNode())) {
                bool samePlane = true;
                bool isCW = true;
                if (edgesVector.size() > 0) {
                    //isCW = iEdge->IsCCWCountingFrom(*edgesVector.back());
                    if (edgesVector.size() > 1) {
                        CreatePlane();
                    } else {
                        FT_DELETE(mTriangle);
                    }
                    if (mTriangle) {
                        samePlane = mTriangle->PlaneContains(iEdge->target());
                    }
                } else {
                    FT_DELETE(mTriangle);
                }
                if (samePlane && isCW)
                {
                    edgesVector.push_back(iEdge);
                    //std::cout << "Route: "; PrintEdgesRoute();
                    
                    if ( Find(iEdge->next()) ) {
                        return true;
                    } else {
                        edgesVector.pop_back();
                    }
                }
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
    if (!mTriangle) {
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
            mTriangle = new Triangle(e1->origin(), e1->target(), e2->target());
            //std::cout << "Created Triangle: " << mTriangle->Description();
        }
    }
}
    
}

