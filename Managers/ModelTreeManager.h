
#pragma once

namespace Factory {

#include <Model/Node.h>
#include <Managers/Octree.h>

//
// Manages model tree
//
class ModelTreeManager
{
public:
    ModelTreeManager();
    ~ModelTreeManager();
    
    void        SetRootNode(Node* pRootNode);
    
    Octree*   Octree() const { return m_pOctree; }
    void        AddNode(Node* pNode);
    void        UpdateNode(Node* pNode);
    void        RemoveNode(Node* pNode);
    
    void PointsInBox(const Box& sBox, std::vector<Point*>& rPointsVector) const {
        m_pOctree->PointsInBox(sBox, rPointsVector);
    }
    unsigned long Size() { return m_pOctree->Size(); }
    
private:
    Node*     m_pRootNode;
    Octree*   m_pOctree;
};

}