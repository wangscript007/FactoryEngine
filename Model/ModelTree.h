
#pragma once


#include <Model/Node.h>
#include <Model/Octree.h>

namespace ftr {
//
// Manages model tree
//
class ModelTree
{
public:
    ModelTree();
    ~ModelTree();
    
    void        setRootNode(Node* pRootNode);
    
    Octree*   Octree() const { return mOctree; }
    void        AddNode(Node* pNode);
    void        UpdateNode(Node* pNode);
    void        RemoveNode(Node* pNode);
    
    void PointNodesInBox(const Box& sBox, std::vector<PointNode*>& pointsVector) const {
        mOctree->PointNodesInBox(sBox, pointsVector);
    }
    unsigned long Size() { return mOctree->Size(); }
    
private:
    Node*     mRootNode;
    ftr::Octree*   mOctree;
};

}