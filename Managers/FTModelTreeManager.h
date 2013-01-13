
#pragma once

#include <Model/FTNode.h>
#include <Managers/FTOctree.h>

//
// Manages model tree
//
class FTModelTreeManager
{
public:
    FTModelTreeManager();
    ~FTModelTreeManager();
    
    void        SetRootNode(FTNode* pRootNode);
    
    FTOctree*   Octree() const { return m_pOctree; }
    void        AddNode(FTNode* pNode);
    void        UpdateNode(FTNode* pNode);
    
    void PointsInBox(const FTBox& sBox, std::vector<FTPoint*>& rPointsVector) const {
        m_pOctree->PointsInBox(sBox, rPointsVector);
    }
    
private:
    FTNode*     m_pRootNode;
    FTOctree*   m_pOctree;
};

