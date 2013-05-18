//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//


#include <Scene/Scene.h>
#include <Render/Layer.h>
#include <Render/LayerRenderer.h>


namespace ftr {


#pragma mark - Super
    
Scene::Scene() :
    mShadersBuilder(NULL),
    mLayerRenderer(NULL),
    mCamera(NULL)
{
    mShadersLibrary = new ShadersLibrary();
    mLightingCollection = new LightingCollection();
    mLayer = new Layer();
    mWorkspace = new Workspace(mLayer);
    mModelManager = new ModelManager();
    mInteractionManager = new class InteractionManager(*mModelManager);
    mModelManager->ModelTreeManager()->setRootNode(reinterpret_cast<Node*>(mWorkspace));
    mModelManager->Select(mWorkspace);
}
    
Scene::~Scene()
{
    FT_DELETE(mWorkspace);
    FT_DELETE(mCamera);
    FT_DELETE(mModelManager);
    FT_DELETE(mInteractionManager);
    FT_DELETE(mLayerRenderer);
    FT_DELETE(mLayer);
    FT_DELETE(mShadersBuilder);
    FT_DELETE(mShadersLibrary);
    FT_DELETE(mLightingCollection);
}
    
void Scene::Prepare()
{
    assert(mShadersBuilder == NULL);
    mShadersBuilder = new ShadersBuilder();
    mShadersBuilder->CreateShadersFromLibrary(*mShadersLibrary);
    mShadersBuilder->CompileShaders();
    mShadersBuilder->LinkProgram();
    mShadersBuilder->shadersProgram()->Activate();
    
    mCamera = new  Camera(Vec3(0.0f, 0.0f, 30.0f));
    mCamera->setProjection(kProjectionPerspective);
    ShadersInput* shadersInput = mShadersBuilder->shadersProgram()->shaderInput();
    mCamera->setShadersInput(shadersInput);
    
    mLayerRenderer = new LayerRenderer(*shadersInput);
    
    glClearColor(0.23f,0.23f,0.23f,1.0);
}

#pragma mark Workspace

void Scene::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //mShadersBuilder->shadersProgram()->Activate();
    mWorkspace->Render(*mLayer);
    mLayerRenderer->Render(*mLayer);
    //mModelManager->ModelTreeManager()->Octree()->Render();
    
    //mShadersBuilder->shadersProgram()->Deactivate();
}
    
void Scene::ActivateProgram()
{
    mShadersBuilder->shadersProgram()->Activate();
}
    
void Scene::DeactivateProgram()
{
    mShadersBuilder->shadersProgram()->Deactivate();
}
    
void Scene::setViewportRect(int x, int y, int width, int height)
{
    mCamera->setViewport(Frame(Vec2(x, y), Vec2(width, height)));
}

#pragma mark Camera
    
void Scene::MoveBy(const Vec2& deltaMove)
{
    mCamera->MoveBy(deltaMove);
}
void Scene::RotateBy(const Vec2& deltaRotation)
{
    mCamera->RotateBy(deltaRotation);
}
void Scene::ZoomBy(const GLfloat times)
{
    mCamera->ZoomBy(times);
}

void Scene::Look()
{
    mCamera->Look();
}
    
void Scene::setProjection(Projection projectionMode)
{
    mCamera->setProjection(projectionMode);
}

#pragma mark Lights


void Scene::TurnOnLight(int index)
{

}
    
#pragma mark Shading
    
void Scene::AddShader(const std::string& name, const std::string& source, GLenum type)
{
    mShadersLibrary->Add(name, source, type);
}

GLuint Scene::ShaderAttributeLocation(const std::string& name)
{
    ShadersInput* input = mShadersBuilder->shadersProgram()->shaderInput();
    return input->AttributeLocation(name);
}

GLuint Scene::ShaderUniformLocation(const std::string& name)
{
    ShadersInput* input = mShadersBuilder->shadersProgram()->shaderInput();
    return input->UniformLocation(name);
}
    
#pragma mark Model

FaceNode* Scene::CreateFace(const Vec3& origin)
{
    return mModelManager->CreateFace(origin, FaceNode::kRectangle);
}


PointNode* Scene::CreatePoint(const Vec3& origin)
{
    return mModelManager->CreatePoint(origin);
}


LineNode* Scene::CreateLine(PointNode* startPoint, PointNode* endPoint)
{
    return mModelManager->CreateLine(startPoint, endPoint);
}

PointNode* Scene::NearestPointToCenterInSphere(const Sphere& sSphere)
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