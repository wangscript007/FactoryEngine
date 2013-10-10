//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//
#pragma once

#include <Model/FaceNode.h>
#include <Workspace/Workspace.h>
#include <Scene/Camera.h>
#include <Model/ModelEditor.h>
#include <Interaction/InteractionProvider.h>
#include <Shading/ShadingLibrary.h>
#include <Lighting/LightingCollection.h>
#include <Leap/LeapListener.h>
#include <Scene/SceneRenderer.h>

namespace ftr {

class Layer;
class LayerRenderer;
    
class Scene
{
public:
                      Scene();
                      ~Scene();
    void              Prepare();
    // Workspace
    void              Render();
    void              setViewportRect(int x, int y, int width, int height);
    
    // Shaders
    void              AddShader(const std::string& name, const std::string& source, GLenum type);
    void              PrepareShadingProgram();
    
    // Model
    void              Select(Node* pNode) { mModelEditor->Select(pNode); }
    FaceNode*         CreateFace(const glm::vec3& origin);
    PointNode*        CreatePoint(const glm::vec3& origin);
    LineNode*         CreateLine(PointNode* startPoint, PointNode* endPoint);
    PointNode*        NearestPointToCenterInSphere(const Sphere& sSphere);
    void              UpdateNode(Node* pNode);
    void              RemoveNode(Node* pNode);
    unsigned long     Size() { return mModelEditor->Size(); }
    
    InteractionProvider* InteractionProvider() const { return mInteractionProvider; }
    Camera*             Camera() const { return mCamera; }
    void                Step(float dTime);
    float               FPS() const { return mFPS; }
    
    Framebuffer*        colorMarkingFramebuffer() const { return mSceneRenderer->colorMarkingFramebuffer(); }
    
        
private:
    Workspace*          mWorkspace;
    class Camera*       mCamera;
    ModelEditor*        mModelEditor;
    ShadingLibrary*     mShadingLibrary;
    LightingCollection* mLightingCollection;
    
    Leap::Controller    mLeapController;
    LeapListener        mleapListener;
    
    Layer*              mLayer;
    SceneRenderer*      mSceneRenderer;
    class InteractionProvider* mInteractionProvider;
    
    float mFPS;
    int mFramesCount;
};

}
