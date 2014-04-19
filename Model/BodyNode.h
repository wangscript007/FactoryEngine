
#pragma once

#include <Model/Node.h>

namespace ftr {

class FaceNode;
class GroupNode;
class PointNode;
class LineNode;
class FaceNode;

class BodyNode : public Node
{
public:
    GroupNode* groupNode() const { return reinterpret_cast<GroupNode*>(Supernode()); }
    
    void AddPointNode(PointNode* pointNode);
    void AddLineNode(LineNode* lineNode);
    void AddFaceNode(FaceNode* faceNode);
    
private:
};

}