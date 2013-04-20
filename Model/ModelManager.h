
#pragma once

#include <Model/ModelFactory.h>
#include <Model/Group.h>
#include <Model/ModelTreeManager.h>

namespace ftr {

class ModelManager
{
public:
                            ModelManager();
                            ~ModelManager();
    
    ModelFactory*         ModelFactory() const { return mModelFactory; }
    ModelTreeManager*     ModelTreeManager() const { return  mModelTreeManager; }
    Point*                NearestPointToCenterInSphere(const Sphere& sSphere) const;
    void                    UpdateNode(Node* pNode) { mModelTreeManager->UpdateNode(pNode); }
    void                    RemoveNode(Node* pNode) { mModelTreeManager->RemoveNode(pNode); }
    void                    Select(Node* pNode);
    Node*                 SelectedNode() const { return mSelectedNode; }
    unsigned long           Size() { return mModelTreeManager->Size(); }
    //
    // Creating
    //
    Face*                 CreateRectangle(const Vec3& origin, const Vec3& size) const;
    Face*                 CreateFace(Vec3 origin, Face::FaceType eType);
    Point*                CreatePoint(Vec3 origin);
    Line*                 CreateLine(Point* startPoint, Point* endPoint);
    
private:
    class ModelFactory*         mModelFactory;
    class ModelTreeManager*     mModelTreeManager;
    Group*                mRootGroup;
    Node*                 mSelectedNode;
};
    
}
