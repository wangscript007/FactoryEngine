
#pragma once


class FTNode;
class FTPoint;

typedef std::vector <FTNode*> TNodesList;

// Controls rendering hierarchy
class FTNode
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
    
                            FTNode();
                            ~FTNode();
    
    virtual void            Render();
    virtual NodeType        Type() const { return kNone; }
    void                    AddNode(FTNode* pNode);
    void                    RemoveNode(FTNode* pMode);
    FTNode*                 Supernode() const { return m_pSupernode; }
    virtual void            Transform(const O5Mat4& m4Transformation);
    virtual std::vector<FTPoint*>* Points() const { return NULL; }
    
private:
    FTNode*                 m_pSupernode;
    TNodesList              m_pSubnodes;
};