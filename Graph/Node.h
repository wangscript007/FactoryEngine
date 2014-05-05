
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
    enum Type {
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
    virtual void            Invalidate();
    virtual Type            Type() const { return kNone; }
  
    void                    AddNode(Node* pNode);
    void                    RemoveNode(Node* pMode);
    Node*                   Supernode() const { return mSupernode; }
    virtual void            Transform(const glm::mat4& m4Transformation);
    virtual std::vector<PointNode*>* PointNodes() const { return NULL; }
    void                    setPickingId(int pickingId);
    int                     pickingId() const { return mPickingId; }
    void                    AddSubnodesWithType(enum Type nodeType, std::vector<Node*>& result) const;
    
    NodesList               mSubnodes;
    
    void                    setSelected(bool selected);
    
protected:
    Node*                   mSupernode;

    int                     mPickingId;
    bool                    mSelected;
    
};

}