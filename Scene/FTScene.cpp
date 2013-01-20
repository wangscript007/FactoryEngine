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
    FTFace* pFace = m_pModelManager->ModelFactory()->CreateRectangleFace(O5Vec3(vOrigin.m_fX, 0.01, vOrigin.m_fZ),
                                                                          O5Vec3(0.0f, 0.0f, 0.0f));
    m_pWorkspace->AddNode(reinterpret_cast<FTFace*>(pFace));
    return pFace;
    
}


FTPoint* FTScene::CreatePoint(O5Vec3 vOrigin)
{
    FTPoint* pPoint = m_pModelManager->ModelFactory()->CreatePoint(O5Vec3(vOrigin.m_fX, vOrigin.m_fY, vOrigin.m_fZ));
    m_pWorkspace->AddNode(reinterpret_cast<FTPoint*>(pPoint));
    return pPoint;
}


FTLine* FTScene::CreateLine(FTPoint* pStartPoint, FTPoint* pEndPoint)
{
    FTLine* pLine = m_pModelManager->ModelFactory()->CreateLine(pStartPoint, pEndPoint);
    m_pWorkspace->AddNode(reinterpret_cast<FTLine*>(pLine));
    return pLine;
}


void FTScene::ChangeFaceSize(O5Vec3 vSize)
{
    
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


