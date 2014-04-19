
#include <Model/BodyNode.h>
#include <Model/FaceNode.h>
#include <Model/LineNode.h>

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
