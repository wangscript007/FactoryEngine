
#pragma once

#include <Model/ModelFactory.h>
#include <Model/GroupNode.h>
#include <Model/ModelTreeManager.h>

namespace ftr {

class ModelManager
{
public:
                            ModelManager();
                            ~ModelManager();
    
    ModelFactory*         ModelFactory() const { return mModelFactory; }
    ModelTreeManager*     ModelTreeManager() const { return  mModelTreeManager; }
    PointNode*                NearestPointToCenterInSphere(const Sphere& sSphere) const;
    void                    UpdateNode(Node* pNode) { mModelTreeManager->UpdateNode(pNode); }
    void                    RemoveNode(Node* pNode) { mModelTreeManager->RemoveNode(pNode); }
    void                    Select(Node* pNode);
    Node*                 SelectedNode() const { return mSelectedNode; }
    unsigned long           Size() { return mModelTreeManager->Size(); }
    //
    // Creating
    //
    FaceNode*                 CreateRectangle(const Vec3& origin, const Vec3& size) const;
    FaceNode*                 CreateFace(Vec3 origin, FaceNode::FaceType eType);
    PointNode*                CreatePoint(Vec3 origin);
    LineNode*                 CreateLine(PointNode* startPoint, PointNode* endPoint);
    
private:
    class ModelFactory*         mModelFactory;
    class ModelTreeManager*     mModelTreeManager;
    Group*                mRootGroup;
    Node*                 mSelectedNode;
};
    
}
