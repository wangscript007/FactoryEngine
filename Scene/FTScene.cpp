//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//

#include <FactoryEngine.h>

#pragma mark - Super
//
//
//
FTScene::FTScene()
{
    glEnable(GL_NORMALIZE);
    m_pWorkspace = new FTWorkspace();
    m_pCamera = new  FTCamera(FTMakeVec3f(5.0f, 5.0f, 5.0f));
    m_pModelManager = new FTModelManager();
    m_pModelManager->m_pModelTreeManager->SetRootNode((FTNode *)m_pWorkspace);
}
//
//
//
FTScene::~FTScene()
{
    
}

#pragma mark Workspace
//
//
//
void FTScene::Render()
{
    m_pWorkspace->Render();
}
//
//
//
void FTScene::SetViewportRect(int x, int y, int width, int height)
{
    m_pWorkspace->SetViewportRect(FTMakeRectf(x, y, width, height));
}

#pragma mark Camera
//
//
//
void FTScene::MoveBy(const FTVec2f deltaMove)
{
    m_pCamera->MoveBy(deltaMove);
}
//
//
//
void FTScene::RotateBy(const FTVec2f deltaRotation)
{
    m_pCamera->RotateBy(deltaRotation);
}
//
//
//
void FTScene::ZoomBy(const GLfloat times)
{
    m_pCamera->ZoomBy(times);
}
//
//
//
void FTScene::Look()
{
    m_pCamera->Look();
}
//
//
//
void FTScene::Reset()
{
    m_pCamera->Reset();
}
//
//
//
void FTScene::SetProjectionMode(FTProjectionMode projectionMode)
{
    m_pCamera->SetProjectionMode(projectionMode);
}

#pragma mark Lights
//
//
//
void FTScene::TurnOnLight(int index)
{
    FTLights::TurnOn(index);
}

#pragma mark Model

//
//
//
void FTScene::CreateFace(FTVec3f vOrigin)
{
    FTFace* pFace = m_pModelManager->m_pModelFactory->CreateRectangleFace(O5Vec3(vOrigin.x, 0.01, vOrigin.z),
                                                                          O5Vec3(1.0f, 0.0f, 1.0f));
    m_pWorkspace->AddNode((FTNode*)pFace);
}
//
//
//
void FTScene::ChangeFaceSize(FTVec3f vSize)
{
    
}


