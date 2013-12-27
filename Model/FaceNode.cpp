
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
    mPolygonPrimitive.color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    Edge* currentEdge = mOuterEdge;
    int i = 0;
    do {
        
        mPolygonPrimitive.mVec[i] = currentEdge->origin();
        i++;
        currentEdge = currentEdge->next();
    } while (currentEdge != mOuterEdge && i < 3);
    mPolygonPrimitive.setOption(Primitive::kUseDepth, true);
    layer.AddPrimitive(mPolygonPrimitive);
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
    do {
        currentEdge->mIncidentFace = this;
        printf("Mark %s\n", currentEdge->Name().c_str());
        currentEdge = currentEdge->next();
        //assert(currentEdge->next()->IsCCWCountingFrom(*currentEdge));
    } while ( currentEdge->IsFree() );
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
