
#include "FTNode.h"

FTNode::FTNode()
{

}

FTNode::~FTNode()
{
}

void FTNode::AddNode(FTNode* node)
{
    mpSubnodes.push_back(node);
    mpSupernode = this;
}

void FTNode::Render()
{
    for(TNodesList::iterator it = mpSubnodes.begin(); it < mpSubnodes.end(); it++)
    {
        (*it)->Render();
    }
}