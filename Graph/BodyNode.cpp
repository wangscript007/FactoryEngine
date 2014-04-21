
#include <Graph/BodyNode.h>
#include <Graph/FaceNode.h>
#include <Graph/LineNode.h>

namespace ftr {

void BodyNode::AddPointNode(PointNode* pointNode)
{
    AddNode(pointNode);
}
    
void BodyNode::AddLineNode(LineNode* lineNode)
{
    AddNode(lineNode);
}
    
void BodyNode::AddFaceNode(FaceNode* faceNode)
{
    AddNode(faceNode);
}
    
}
