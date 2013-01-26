//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//
#pragma once

#include <Model/FTFace.h>
#include <Workspace/FTWorkspace.h>
#include <Surround/FTCamera.h>
#include <Managers/FTModelManager.h>
#include <Managers/FTInteractionManager.h>

class FTScene
{
public:
                        FTScene();
                        ~FTScene();
    //
    // Workspace
    //
    void                Render();
    void                SetViewportRect(int x, int y, int width, int height);
    //
    // Camera
    //
    void                MoveBy(const O5Vec2 deltaMove);
    void                RotateBy(const O5Vec2 deltaRotation);
    void                ZoomBy(const GLfloat times);
    void                Look();
    void                Reset();
    void                SetProjectionMode(FTProjectionMode projectionMode);
    //
    // Lights           
    //
    void                TurnOnLight(int index);
    //
    // Model
    //
    void                Select(FTNode* pNode) { m_pModelManager->Select(pNode); }
    FTFace*             CreateFace(O5Vec3 vOrigin);
    FTPoint*            CreatePoint(O5Vec3 vOrigin);
    FTLine*             CreateLine(FTPoint* pStartPoint, FTPoint* pEndPoint);
    FTPoint*            NearestPointToCenterInSphere(const FTSphere& sSphere);
    void                UpdateNode(FTNode* pNode);
    void                RemoveNode(FTNode* pNode);
    unsigned long       Size() { return m_pModelManager->Size(); }
    
    FTInteractionManager* InteractionManager() const { return m_pInteractionManager; }
    
private:
    
    FTWorkspace*        m_pWorkspace;
    FTCamera*           m_pCamera;
    FTModelManager*     m_pModelManager;
    FTInteractionManager* m_pInteractionManager;
    
};

