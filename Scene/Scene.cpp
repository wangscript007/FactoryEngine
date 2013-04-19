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
    mWorkspace = new Workspace();
    mCamera = new  Camera(Vec3(5.0f, 5.0f, 5.0f));
    mModelManager = new ModelManager();
    mModelManager->ModelTreeManager()->setRootNode(reinterpret_cast<Node*>(mWorkspace));
    mInteractionManager = new class InteractionManager(*mModelManager);
    
    Select(mWorkspace);
}
//
//
//
Scene::~Scene()
{
    FT_DELETE(mWorkspace);
    FT_DELETE(mCamera);
    FT_DELETE(mModelManager);
    FT_DELETE(mInteractionManager);
}

#pragma mark Workspace
//
//
//
void Scene::Render()
{
    mWorkspace->Render();
    mModelManager->ModelTreeManager()->Octree()->Render();
}
//
//
//
void Scene::setViewportRect(int x, int y, int width, int height)
{
    mWorkspace->setViewportRect(Rect(x, y, width, height));
}

#pragma mark Camera
//
//
//
void Scene::MoveBy(const Vec2& deltaMove)
{
    mCamera->MoveBy(deltaMove);
}
//
//
//
void Scene::RotateBy(const Vec2& deltaRotation)
{
    mCamera->RotateBy(deltaRotation);
}
//
//
//
void Scene::ZoomBy(const GLfloat times)
{
    mCamera->ZoomBy(times);
}
//
//
//
void Scene::Look()
{
    mCamera->Look();
}
//
//
//
void Scene::Reset()
{
    mCamera->Reset();
}
//
//
//
void Scene::setProjectionMode(ProjectionMode projectionMode)
{
    mCamera->setProjectionMode(projectionMode);
}

#pragma mark Lights


void Scene::TurnOnLight(int index)
{
    Lights::TurnOn(index);
}

#pragma mark Model

Face* Scene::CreateFace(const Vec3& origin)
{
    return mModelManager->CreateFace(origin, Face::kRectangle);
}


Point* Scene::CreatePoint(const Vec3& origin)
{
    return mModelManager->CreatePoint(origin);
}


Line* Scene::CreateLine(Point* startPoint, Point* endPoint)
{
    return mModelManager->CreateLine(startPoint, endPoint);
}

Point* Scene::NearestPointToCenterInSphere(const Sphere& sSphere)
{
    return mModelManager->NearestPointToCenterInSphere(sSphere);
}

void Scene::UpdateNode(Node* pNode)
{
    mModelManager->UpdateNode(pNode);
}

void Scene::RemoveNode(Node* pNode)
{
    mModelManager->RemoveNode(pNode);
    mWorkspace->RemoveNode(pNode);
}

}