
#pragma once

#include <Render/Layer.h>
#include <Render/Primitive.h>

namespace ftr {
    
class Node;
class PointNode;

typedef std::vector <Node*> NodesList;

// Scene tree element
class Node
{
public:
    enum NodeType {
        kNone,
        kPoint,
        kLine,
        kFace,
        kBody,
        kGroup
    };
    
                            Node();
                            ~Node();
    
    virtual void            Render(Layer& layer);
    virtual NodeType        Type() const { return kNone; }
    void                    AddNode(Node* pNode);
    void                    RemoveNode(Node* pMode);
    Node*                   Supernode() const { return mSupernode; }
    virtual void            Transform(const Mat4& m4Transformation);
    virtual std::vector<PointNode*>* PointNodes() const { return NULL; }
    
private:
    Node*                   mSupernode;
    NodesList               mSubnodes;
};

}