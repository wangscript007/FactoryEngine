//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//
#pragma once



#include <Model/Face.h>
#include <Workspace/Workspace.h>
#include <Surround/Camera.h>
#include <Managers/ModelManager.h>
#include <Managers/InteractionManager.h>

namespace Factory {

class Scene
{
public:
                        Scene();
                        ~Scene();
    //
    // Workspace
    //
    void                Render();
    void                SetViewportRect(int x, int y, int width, int height);
    //
    // Camera
    //
    void                MoveBy(const Vec2 deltaMove);
    void                RotateBy(const Vec2 deltaRotation);
    void                ZoomBy(const GLfloat times);
    void                Look();
    void                Reset();
    void                SetProjectionMode(ProjectionMode projectionMode);
    //
    // Lights           
    //
    void                TurnOnLight(int index);
    //
    // Model
    //
    void                Select(Node* pNode) { m_pModelManager->Select(pNode); }
    Face*             CreateFace(Vec3 vOrigin);
    Point*            CreatePoint(Vec3 vOrigin);
    Line*             CreateLine(Point* pStartPoint, Point* pEndPoint);
    Point*            NearestPointToCenterInSphere(const Sphere& sSphere);
    void                UpdateNode(Node* pNode);
    void                RemoveNode(Node* pNode);
    unsigned long       Size() { return m_pModelManager->Size(); }
    
    InteractionManager* InteractionManager() const { return m_pInteractionManager; }
    
private:
    
    Workspace*        m_pWorkspace;
    Camera*           m_pCamera;
    ModelManager*     m_pModelManager;
    class InteractionManager* m_pInteractionManager;
    
};

}
