//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//


#include <Scene/Scene.h>
#include <Surround/Lights.h>

namespace ftr {


#pragma mark - Super
//
//
//
Scene::Scene()
{
    glEnable(GL_NORMALIZE);
    m_pWorkspace = new Workspace();
    m_pCamera = new  Camera(Vec3(5.0f, 5.0f, 5.0f));
    m_pModelManager = new ModelManager();
    m_pModelManager->ModelTreeManager()->SetRootNode(reinterpret_cast<Node*>(m_pWorkspace));
    m_pInteractionManager = new class InteractionManager(*m_pModelManager);
    
    Select(m_pWorkspace);
}
//
//
//
Scene::~Scene()
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
void Scene::Render()
{
    m_pWorkspace->Render();
    m_pModelManager->ModelTreeManager()->Octree()->Render();
}
//
//
//
void Scene::SetViewportRect(int x, int y, int width, int height)
{
    m_pWorkspace->SetViewportRect(Rect(x, y, width, height));
}

#pragma mark Camera
//
//
//
void Scene::MoveBy(const Vec2 deltaMove)
{
    m_pCamera->MoveBy(deltaMove);
}
//
//
//
void Scene::RotateBy(const Vec2 deltaRotation)
{
    m_pCamera->RotateBy(deltaRotation);
}
//
//
//
void Scene::ZoomBy(const GLfloat times)
{
    m_pCamera->ZoomBy(times);
}
//
//
//
void Scene::Look()
{
    m_pCamera->Look();
}
//
//
//
void Scene::Reset()
{
    m_pCamera->Reset();
}
//
//
//
void Scene::SetProjectionMode(ProjectionMode projectionMode)
{
    m_pCamera->SetProjectionMode(projectionMode);
}

#pragma mark Lights


void Scene::TurnOnLight(int index)
{
    Lights::TurnOn(index);
}

#pragma mark Model

Face* Scene::CreateFace(Vec3 vOrigin)
{
    return m_pModelManager->CreateFace(vOrigin, Face::kRectangle);
}


Point* Scene::CreatePoint(Vec3 vOrigin)
{
    return m_pModelManager->CreatePoint(vOrigin);
}


Line* Scene::CreateLine(Point* pStartPoint, Point* pEndPoint)
{
    return m_pModelManager->CreateLine(pStartPoint, pEndPoint);
}

Point* Scene::NearestPointToCenterInSphere(const Sphere& sSphere)
{
    return m_pModelManager->NearestPointToCenterInSphere(sSphere);
}

void Scene::UpdateNode(Node* pNode)
{
    m_pModelManager->UpdateNode(pNode);
}

void Scene::RemoveNode(Node* pNode)
{
    m_pModelManager->RemoveNode(pNode);
    m_pWorkspace->RemoveNode(pNode);
}

}