
#pragma once

namespace Factory {
    
class Node;
class Point;

typedef std::vector <Node*> TNodesList;

// Controls rendering hierarchy
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
    
    virtual void            Render();
    virtual NodeType        Type() const { return kNone; }
    void                    AddNode(Node* pNode);
    void                    RemoveNode(Node* pMode);
    Node*                 Supernode() const { return m_pSupernode; }
    virtual void            Transform(const O5Mat4& m4Transformation);
    virtual std::vector<Point*>* Points() const { return NULL; }
    
private:
    Node*                 m_pSupernode;
    TNodesList              m_pSubnodes;
};

}