
#include <Model/FaceNode.h>
#include <Model/LineNode.h>
#include <Model/PointNode.h>
#include <Model/HalfEdge.h>
#include <Main/Log.h>

namespace ftr {

FaceNode::FaceNode()
{
    
}


void FaceNode::Render(Layer& layer)
{
    Node::Render(layer);
    
}

#pragma mark - Instance
    
void FaceNode::BoundByLoopWithHalfEdge(HalfEdge& outerEdge)
{
    mOuterEdge = &outerEdge;
    MarkIncidentFaceInLoopWithHalfEdge(outerEdge);
}
    
void FaceNode::AddHoleBoundedByLoopWithHalfEdge(HalfEdge& innerEdge)
{
    mInnerEdges.push_back(&innerEdge);
    MarkIncidentFaceInLoopWithHalfEdge(innerEdge);
}
    
void FaceNode::MarkIncidentFaceInLoopWithHalfEdge(HalfEdge& halfEdge)
{
    HalfEdge* currentEdge = &halfEdge;
    currentEdge->mIncidentFace = this;
    while (currentEdge->HasFreeNextEdge() && (currentEdge->next() != &halfEdge)) {
        currentEdge = currentEdge->next();
        currentEdge->mIncidentFace = this;
    }
}

std::string FaceNode::Description() const
{
    std::string description = "";
    HalfEdge* currentEdge = mOuterEdge;
    while (currentEdge->next() && (currentEdge->next() != mOuterEdge)) {
        currentEdge = currentEdge->next();
        description += currentEdge->originNode()->mName + "-";
    }
    description += currentEdge->next()->originNode()->mName;
    return description;
}

}
