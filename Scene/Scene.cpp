//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//


#include <Scene/Scene.h>
#include <Render/Layer.h>
#include <Render/LayerRenderer.h>


namespace ftr {


#pragma mark - Super
    
Scene::Scene() :
    mSceneRenderer(NULL),
    mCamera(NULL), 
    mFramesCount(0)
{
    mShadingLibrary = new ShadingLibrary();
    mLightingCollection = new LightingCollection();
    mLayer = new Layer();
    mWorkspace = new Workspace(mLayer);
    mModelEditor = new ModelEditor();
    mModelEditor->ModelTree()->setRootNode(reinterpret_cast<Node*>(mWorkspace));
    mModelEditor->Select(mWorkspace);
    
    mLeapController.addListener(mleapListener);
}
    
Scene::~Scene()
{
    FT_DELETE(mWorkspace);
    FT_DELETE(mCamera);
    FT_DELETE(mModelEditor);
    FT_DELETE(mInteractionProvider);
    FT_DELETE(mSceneRenderer);
    FT_DELETE(mLayer);
    FT_DELETE(mShadingLibrary);
    FT_DELETE(mLightingCollection);
}
    
void Scene::Prepare()
{
    mCamera = new class Camera(Vec3(0.0f, 0.0f, 10.0f));
    mCamera->setProjection(kProjectionPerspective);
    mShadingLibrary->BuildProgramWithType(ShadingProgram::kMain);
    mShadingLibrary->BuildProgramWithType(ShadingProgram::kColor);
    
    ShadingInterface& shadingInterface = mShadingLibrary->interface();
    mCamera->setShadingInterface(&shadingInterface);
    mInteractionProvider = new class InteractionProvider(*mModelEditor, *mCamera);
    mleapListener.setCameraInteraction(mInteractionProvider->CameraInteraction());
    
    mShadingLibrary->UseProgramWithType(ShadingProgram::kMain);
    LightingModel* activeLightingModel = mLightingCollection->activeModel();
    activeLightingModel->setShadingInterface(&shadingInterface);
    activeLightingModel->SetupLights();
    activeLightingModel->SendDataToShader();
    mSceneRenderer = new SceneRenderer(*mShadingLibrary);
}

#pragma mark Workspace

void Scene::Render()
{
    mCamera->Look();
    mWorkspace->Render(*mLayer);
    mSceneRenderer->Render(*mLayer);
    mLayer->Clear();
    mFramesCount++;
}
    
void Scene::setViewportRect(int x, int y, int width, int height)
{
    Frame frame = Frame(Vec2(x, y), Vec2(width, height));
    mCamera->setViewport(frame);
    mSceneRenderer->setFrame(frame);
}
    
void Scene::Step(float dTime)
{
    mFPS = mFramesCount/dTime;
    mFramesCount = 0;
}

#pragma mark Lights
    
#pragma mark Shading
    
void Scene::AddShader(const std::string& name, const std::string& source, GLenum type)
{
    mShadingLibrary->Add(name, source, type);
}
    
#pragma mark Model

FaceNode* Scene::CreateFace(const Vec3& origin)
{
    return mModelEditor->CreateFace(origin, FaceNode::kRectangle);
}


PointNode* Scene::CreatePoint(const Vec3& origin)
{
    return mModelEditor->CreatePoint(origin);
}


LineNode* Scene::CreateLine(PointNode* startPoint, PointNode* endPoint)
{
    return mModelEditor->CreateLine(startPoint, endPoint);
}

PointNode* Scene::NearestPointToCenterInSphere(const Sphere& sSphere)
{
    return mModelEditor->NearestPointToCenterInSphere(sSphere);
}

void Scene::UpdateNode(Node* pNode)
{
    mModelEditor->UpdateNode(pNode);
}

void Scene::RemoveNode(Node* pNode)
{
    mModelEditor->RemoveNode(pNode);
    mWorkspace->RemoveNode(pNode);
}

}