
#pragma once


class FTNode;

typedef std::vector <FTNode*> TNodesList;

// Controls rendering hierarchy
class FTNode
{
public:
                            FTNode();
                            ~FTNode();
    FTNode*                 m_pSupernode;
    TNodesList              m_pSubnodes;
    void                    AddNode(FTNode* pNode);
    void                    RemoveNode(FTNode* pMode);
    
public:
    virtual void            Render();
};