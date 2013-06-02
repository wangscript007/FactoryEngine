
#pragma once

#include <Model/ModelFactory.h>
#include <Model/GroupNode.h>
#include <Model/ModelTree.h>

namespace ftr {

class ModelEditor
{
public:
                            ModelEditor();
                            ~ModelEditor();
    
    ModelFactory*         ModelFactory() const { return mModelFactory; }
    ModelTree*     ModelTree() const { return  mModelTree; }
    PointNode*                NearestPointToCenterInSphere(const Sphere& sSphere) const;
    void                    UpdateNode(Node* pNode) { mModelTree->UpdateNode(pNode); }
    void                    RemoveNode(Node* pNode) { mModelTree->RemoveNode(pNode); }
    void                    Select(Node* pNode);
    Node*                 SelectedNode() const { return mSelectedNode; }
    unsigned long           Size() { return mModelTree->Size(); }
    //
    // Creating
    //
    FaceNode*                 CreateRectangle(const Vec3& origin, const Vec3& size) const;
    FaceNode*                 CreateFace(Vec3 origin, FaceNode::FaceType eType);
    PointNode*                CreatePoint(Vec3 origin);
    LineNode*                 CreateLine(PointNode* startPoint, PointNode* endPoint);
    
private:
    class ModelFactory*         mModelFactory;
    class ModelTree*     mModelTree;
    Group*                mRootGroup;
    Node*                 mSelectedNode;
};
    
}
