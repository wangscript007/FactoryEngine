//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//
#include <Scene/Scene.h>
#include <Scene/Picker.h>
#include <Render/Layer.h>
#include <Render/LayerRenderer.h>
#include <Scene/Viewport.h>
#include <Shading/ShadingLibrary.h>
#include <Workspace/Workspace.h>
#include <Lighting/LightingCollection.h>
#include <ImportExport/ModelImporter.h>

namespace ftr {


#pragma mark - Super
    
Scene::Scene() :
    mSceneRenderer(NULL),
    mCamera(NULL), 
    mFramesCount(0),
    mOptions(kOptionShowNone)
{
    mShadingLibrary = new ShadingLibrary();
    mLightingCollection = new LightingCollection();
    mLayer = new Layer();
    mWorkspace = new Workspace(mLayer);

    mModelEditor = new ModelEditor();
    //mModelEditor->DebugCreateCube();
    
    ModelImporter modelImporter(*mModelEditor);
    
    modelImporter.Import("/Users/edvinassarkus/factory/factoryengine/Tests/Models/X/dwarf.x");


    mWorkspace->setOctree(*mModelEditor->modelTree()->Octree());
    mWorkspace->setModelTree(mModelEditor->modelTree());
#ifdef LEAP_ENABLED
    mLeapController.addListener(mleapListener);
#endif
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
    FT_DELETE(mPicker);
}
    
void Scene::setOption(Option option, bool value)
{
    if (value) {
        mOptions |= static_cast<unsigned int>(option);
    } else {
        mOptions &= ~(static_cast<unsigned int>(option));
    }
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
#ifdef LEAP_ENABLED
    mleapListener.setCameraInteraction(mInteractionProvider->CameraInteraction());
#endif

    mShadingLibrary->UseProgramWithType(ShadingProgram::kMain);
    
    LightingModel* activeLightingModel = mLightingCollection->activeModel();
    activeLightingModel->setShadingInterface(&shadingInterface);
    activeLightingModel->SetupLights();
    activeLightingModel->SendDataToShader();
    mSceneRenderer = new SceneRenderer(*mShadingLibrary, *mCamera);
    
    mPicker = new Picker(*mModelEditor->modelTree(), *mSceneRenderer);
    mModelEditor->setPicker(mPicker);
}

#pragma mark Workspace

void Scene::Render()
{
    mSceneRenderer->setMarkingBufferVisible(option(kOptionShowMarkingView));
    mWorkspace->mRenderOctree = option(kOptionShowOctree);

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


}