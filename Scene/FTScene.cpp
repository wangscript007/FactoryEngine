//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//


#include <Scene/FTScene.h>
#include <Surround/FTLights.h>


#pragma mark - Super
//
//
//
FTScene::FTScene()
{
    glEnable(GL_NORMALIZE);
    m_pWorkspace = new FTWorkspace();
    m_pCamera = new  FTCamera(O5Vec3(5.0f, 5.0f, 5.0f));
    m_pModelManager = new FTModelManager();
    m_pModelManager->ModelTreeManager()->SetRootNode(reinterpret_cast<FTNode*>(m_pWorkspace));
    m_pInteractionManager = new FTInteractionManager(*m_pModelManager);
    
    Select(m_pWorkspace);
}
//
//
//
FTScene::~FTScene()
{
    FT_DELETE(m_pWorkspace);
    FT_DELETE(m_pCamera);
    FT_DELETE(m_pModelManager);
    FT_DELETE(m_pInteractionManager);
}

#pragma mark Workspace
//
//
//
void FTScene::Render()
{
    m_pWorkspace->Render();
    m_pModelManager->ModelTreeManager()->Octree()->Render();
}
//
//
//
void FTScene::SetViewportRect(int x, int y, int width, int height)
{
    m_pWorkspace->SetViewportRect(FTRect(x, y, width, height));
}

#pragma mark Camera
//
//
//
void FTScene::MoveBy(const O5Vec2 deltaMove)
{
    m_pCamera->MoveBy(deltaMove);
}
//
//
//
void FTScene::RotateBy(const O5Vec2 deltaRotation)
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


void FTScene::TurnOnLight(int index)
{
    FTLights::TurnOn(index);
}

#pragma mark Model

FTFace* FTScene::CreateFace(O5Vec3 vOrigin)
{
    return m_pModelManager->CreateFace(vOrigin, FTFace::kRectangle);
}


FTPoint* FTScene::CreatePoint(O5Vec3 vOrigin)
{
    return m_pModelManager->CreatePoint(vOrigin);
}


FTLine* FTScene::CreateLine(FTPoint* pStartPoint, FTPoint* pEndPoint)
{
    return m_pModelManager->CreateLine(pStartPoint, pEndPoint);
}

FTPoint* FTScene::NearestPointToCenterInSphere(const FTSphere& sSphere)
{
    return m_pModelManager->NearestPointToCenterInSphere(sSphere);
}

void FTScene::UpdateNode(FTNode* pNode)
{
    m_pModelManager->UpdateNode(pNode);
}

void FTScene::RemoveNode(FTNode* pNode)
{
    m_pModelManager->RemoveNode(pNode);
    m_pWorkspace->RemoveNode(pNode);
}


