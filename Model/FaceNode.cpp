
#include <Model/FaceNode.h>
#include <Model/LineNode.h>
#include <Model/PointNode.h>
#include <Model/Edge.h>
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
    
void FaceNode::BoundByLoopWithEdge(Edge& outerEdge)
{
    mOuterEdge = &outerEdge;
    MarkIncidentFaceInLoopWithEdge(outerEdge);
}
    
void FaceNode::AddHoleBoundedByLoopWithEdge(Edge& innerEdge)
{
    mInnerEdges.push_back(&innerEdge);
    MarkIncidentFaceInLoopWithEdge(innerEdge);
}
    
void FaceNode::MarkIncidentFaceInLoopWithEdge(Edge& edge)
{
    Edge* currentEdge = &edge;
    currentEdge->mIncidentFace = this;
    while (currentEdge->HasFreeNextEdge() && (currentEdge->next() != &edge)) {
        currentEdge = currentEdge->next();
        currentEdge->mIncidentFace = this;
    }
}

std::string FaceNode::Description() const
{
    std::string description = "";
    Edge* currentEdge = mOuterEdge;
    while (currentEdge->next() && (currentEdge->next() != mOuterEdge)) {
        currentEdge = currentEdge->next();
        description += currentEdge->originNode()->mName + "-";
    }
    description += currentEdge->next()->originNode()->mName;
    return description;
}

}
