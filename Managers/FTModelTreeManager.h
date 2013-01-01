
#pragma once

#include "../Model/FTNode.h"
#include "FTOctree.h"

class FTModelTreeManager
{
public:
    FTModelTreeManager();
    ~FTModelTreeManager();
    
    void        SetRootNode(FTNode* pRootNode);
    
    FTOctree*   Octree() const { return m_pOctree; }

private:
    FTNode*     m_pRootNode;
    FTOctree*   m_pOctree;
    
};

