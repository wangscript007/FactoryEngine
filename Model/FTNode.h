
#pragma once


class FTNode;

typedef std::vector <FTNode*> TNodesList;

// Controls rendering hierarchy
class FTNode
{
public:
                            FTNode();
                            ~FTNode();
    FTNode*                 mpSupernode;
    TNodesList              mpSubnodes;
    void                    AddNode(FTNode* node);
    
public:
    virtual void            Render();
};