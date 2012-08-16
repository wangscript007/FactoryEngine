class FTNode;
typedef std::vector <FTNode*> NodesList;

// Controls rendering hierarchy
class FTNode
{
public:
                            FTNode();
                            ~FTNode();
    FTNode*                 mpSupernode;
    NodesList               mpSubnodes;
public:
    void                    AddNode(FTNode* node);
    virtual void            Render();
};