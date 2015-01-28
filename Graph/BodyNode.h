
#pragma once

#include <Graph/Node.h>

namespace ftr {

class FaceNode;
class GroupNode;
class PointNode;
class LineNode;
class FaceNode;

class BodyNode : public Node
{
public:
    virtual enum Type Type() const { return kBody; }
    
    GroupNode* groupNode() const { return reinterpret_cast<GroupNode*>(Supernode()); }
    
    void AddPointNode(PointNode* pointNode);
    void AddLineNode(LineNode* lineNode);
    void AddFaceNode(FaceNode* faceNode);
    
    virtual char Depth() const { return 0; }
private:
};

}