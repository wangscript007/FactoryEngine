
#pragma once


#include <Model/Node.h>
#include <Managers/Octree.h>

namespace ftr {
//
// Manages model tree
//
class ModelTreeManager
{
public:
    ModelTreeManager();
    ~ModelTreeManager();
    
    void        setRootNode(Node* pRootNode);
    
    Octree*   Octree() const { return mOctree; }
    void        AddNode(Node* pNode);
    void        UpdateNode(Node* pNode);
    void        RemoveNode(Node* pNode);
    
    void PointsInBox(const Box& sBox, std::vector<Point*>& pointsVector) const {
        mOctree->PointsInBox(sBox, pointsVector);
    }
    unsigned long Size() { return mOctree->Size(); }
    
private:
    Node*     mRootNode;
    ftr::Octree*   mOctree;
};

}