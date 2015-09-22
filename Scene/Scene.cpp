//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//
#include <Scene/Scene.h>
#include <Scene/Picker.h>
#include <Render/Layer.h>
#include <Render/LayerRenderer.h>
#include <Scene/Viewport.h>
#include <Workspace/Workspace.h>
//#include <ImportExport/ModelImporter.h>
#include <Query/Query.h>

namespace ftr {


#pragma mark - Super
    
Scene::Scene() :
    mSceneRenderer(NULL),
    mCamera(NULL), 
    mFramesCount(0),
    mOptions(kOptionShowNone)
{

    ShadingInterface& shadingInterface = *new ShadingInterface();
    
    
    mCamera = new class Camera(mViewport);
    mCamera->setShadingInterface(&shadingInterface);
    
    mSceneRenderer = new SceneRenderer(*mCamera);

    
    mLayer = new Layer();
    mWorkspace = new Workspace(mLayer);

    mModelEditor = new ModelEditor();
//    mModelEditor->DebugCreateCube();
    
    mPicker = new Picker(*mModelEditor->modelTree(), *mSceneRenderer, *mLayer);
    mModelEditor->setPicker(mPicker);
    mInteractionProvider = new class InteractionProvider(*mModelEditor, *mCamera);

    
//    ModelImporter modelImporter(*mModelEditor);

    //modelImporter.Import("/Users/edvinassarkus/factory/factoryengine/Tests/Models/HMP/terrain_withtexture.hmp");
    
    //modelImporter.Import("/Users/edvinassarkus/factory/factoryengine/Tests/Models/B3D/turtle1.b3d");
    //modelImporter.Import("/Users/edvinassarkus/factory/factoryengine/Tests/Models/DXF/rifle.dxf");
    //modelImporter.Import("/Users/edvinassarkus/factory/factoryengine/Tests/Models/LWO/LWO2/rifle.lwo");
    //modelImporter.Import("/Users/edvinassarkus/factory/factoryengine/Tests/Models/X/dwarf.x");


    mWorkspace->setOctree(*mModelEditor->modelTree()->Octree());
    mWorkspace->setModelTree(mModelEditor->modelTree());
    
    mQuery = new Query(*mModelEditor->modelTree());
}
    
Scene::~Scene()
{
    FT_DELETE(mWorkspace);
    FT_DELETE(mCamera);
    FT_DELETE(mModelEditor);
    FT_DELETE(mInteractionProvider);
    FT_DELETE(mSceneRenderer);
    FT_DELETE(mLayer);
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
    
void Scene::Reset()
{
    mLayer->Clear();
//    mShadingLibrary->clear();
}
    
void Scene::Prepare()
{
//    glClearColor(0.1f, 0.3f, 0.1f,1.0);
//    mShadingLibrary->BuildProgramWithType(ShadingProgram::kMain);
//    mShadingLibrary->BuildProgramWithType(ShadingProgram::kColor);
//    mShadingLibrary->UseProgramWithType(ShadingProgram::kMain);
    
    mCamera->setProjection(kProjectionPerspective);
    
}

#pragma mark Workspace

void Scene::Render()
{
    mSceneRenderer->setMarkingBufferVisible(option(kOptionShowMarkingView));
    mWorkspace->SetRenderOctree(option(kOptionShowOctree));
    mLayer->Cleanup();
    mWorkspace->Render(*mLayer);
    mSceneRenderer->Render(*mLayer);
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
    

}