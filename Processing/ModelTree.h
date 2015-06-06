
#pragma once

#include <Graph/Node.h>
#include <Processing/Octree.h>

namespace ftr {
//
// Manages model tree
//
    
class GroupNode;
class FaceNode;

class ModelTree
{
public:
    ModelTree();
    ~ModelTree();
    
    void Render(Layer& layer);
    
    
    Octree*     Octree() const { return mOctree; }
    
    void        AddGroup(GroupNode* groupNode);
    
    void        AddNode(Node* pNode);
    void        UpdateNode(Node* pNode);
    void        RemoveNode(Node* pNode);
    
    void PointNodesInBox(const Box& sBox, std::vector<PointNode*>& pointsVector) const {
        mOctree->PointNodesInBox(sBox, pointsVector);
    }
    void PointNodesInCylinder(const Cylinder& cylinder, std::vector<PointNode*>& pointsVector) const {
        mOctree->PointNodesInCylinder(cylinder, pointsVector);
    }
    void PointNodes(std::vector<PointNode*>& pointsVector) const {
        mOctree->PointNodes(pointsVector);
    }
    
    void FaceNodes(std::vector<FaceNode*>& faceNodes) const;
  


    unsigned long Size() { return mOctree->Size(); }
    
    std::vector<GroupNode*> mGroups;
    
private:
    ftr::Octree* mOctree;
};

}