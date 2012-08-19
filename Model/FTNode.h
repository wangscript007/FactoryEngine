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
    void                    AddNode(FTNode* node);
public:
    virtual void            Render();
};