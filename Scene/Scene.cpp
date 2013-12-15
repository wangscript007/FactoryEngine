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
    mCamera = new class Camera(mViewport);
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
    mSceneRenderer = new SceneRenderer(*mShadingLibrary, *mCamera);
}

#pragma mark Workspace

void Scene::Render()
{
    mWorkspace->Render(*mLayer);
    mSceneRenderer->Render(*mLayer);
    mLayer->Clear();
    mFramesCount++;
}
    
void Scene::setViewportRect(int x, int y, int width, int height)
{
    glm::vec4 frame =  glm::vec4(glm::vec2(x, y), glm::vec2(width, height));
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

PointNode* Scene::CreatePoint(const glm::vec3& origin)
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