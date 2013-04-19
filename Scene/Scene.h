//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//
#pragma once



#include <Model/Face.h>
#include <Workspace/Workspace.h>
#include <Surround/Camera.h>
#include <Managers/ModelManager.h>
#include <Managers/InteractionManager.h>

namespace ftr {

class Scene
{
public:
                        Scene();
                        ~Scene();
    //
    // Workspace
    //
    void                Render();
    void                setViewportRect(int x, int y, int width, int height);
    //
    // Camera
    //
    void                MoveBy(const Vec2& deltaMove);
    void                RotateBy(const Vec2& deltaRotation);
    void                ZoomBy(const GLfloat times);
    void                Look();
    void                Reset();
    void                setProjectionMode(ProjectionMode projectionMode);
    //
    // Lights           
    //
    void                TurnOnLight(int index);
    //
    // Model
    //
    void                Select(Node* pNode) { mModelManager->Select(pNode); }
    Face*               CreateFace(const Vec3& origin);
    Point*              CreatePoint(const Vec3& origin);
    Line*               CreateLine(Point* startPoint, Point* endPoint);
    Point*              NearestPointToCenterInSphere(const Sphere& sSphere);
    void                UpdateNode(Node* pNode);
    void                RemoveNode(Node* pNode);
    unsigned long       Size() { return mModelManager->Size(); }
    
    InteractionManager* InteractionManager() const { return mInteractionManager; }
    
private:
    
    Workspace*        mWorkspace;
    Camera*           mCamera;
    ModelManager*     mModelManager;
    class InteractionManager* mInteractionManager;
    
};

}
