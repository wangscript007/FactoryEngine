//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//
#pragma once



#include <Model/FaceNode.h>
#include <Workspace/Workspace.h>
#include <Surround/Camera.h>
#include <Model/ModelManager.h>
#include <Interaction/InteractionManager.h>

namespace ftr {

class RenderBundle;
class BundleRenderer;
    
class Scene
{
public:
                      Scene();
                      ~Scene();
    //
    // Workspace
    //
    void              Render();
    void              setViewportRect(int x, int y, int width, int height);
    //
    // Camera
    //
    void              MoveBy(const Vec2& deltaMove);
    void              RotateBy(const Vec2& deltaRotation);
    void              ZoomBy(const GLfloat times);
    void              Look();
    void              Reset();
    void              setProjectionMode(ProjectionMode projectionMode);
    //
    // Lights           
    //
    void              TurnOnLight(int index);
    //
    // Model
    //
    void              Select(Node* pNode) { mModelManager->Select(pNode); }
    FaceNode*         CreateFace(const Vec3& origin);
    PointNode*        CreatePoint(const Vec3& origin);
    LineNode*         CreateLine(PointNode* startPoint, PointNode* endPoint);
    PointNode*        NearestPointToCenterInSphere(const Sphere& sSphere);
    void              UpdateNode(Node* pNode);
    void              RemoveNode(Node* pNode);
    unsigned long     Size() { return mModelManager->Size(); }
    
    InteractionManager* InteractionManager() const { return mInteractionManager; }
    
private:
    
    Workspace*        mWorkspace;
    Camera*           mCamera;
    ModelManager*     mModelManager;
    
    RenderBundle*     mRenderBundle;
    BundleRenderer*   mBundleRenderer;
    class InteractionManager* mInteractionManager;
    
};

}
