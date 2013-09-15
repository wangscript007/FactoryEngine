//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//
#pragma once

#include <Model/FaceNode.h>
#include <Workspace/Workspace.h>
#include <Scene/Camera.h>
#include <Model/ModelEditor.h>
#include <Interaction/InteractionProvider.h>
#include <Shading/ShadersBuilder.h>
#include <Shading/ShadersLibrary.h>
#include <Lighting/LightingCollection.h>
#include <Leap/LeapListener.h>

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
    void              PrepareShadersProgram();
    void              ActivateProgram();
    GLuint            ShaderAttributeLocation(const std::string& name);
    GLuint            ShaderUniformLocation(const std::string& name);

    void              DeactivateProgram();
    
    // Model
    void              Select(Node* pNode) { mModelEditor->Select(pNode); }
    FaceNode*         CreateFace(const Vec3& origin);
    PointNode*        CreatePoint(const Vec3& origin);
    LineNode*         CreateLine(PointNode* startPoint, PointNode* endPoint);
    PointNode*        NearestPointToCenterInSphere(const Sphere& sSphere);
    void              UpdateNode(Node* pNode);
    void              RemoveNode(Node* pNode);
    unsigned long     Size() { return mModelEditor->Size(); }
    
    InteractionProvider* InteractionProvider() const { return mInteractionProvider; }
    Camera*             Camera() const { return mCamera; }
    
private:
    Workspace*          mWorkspace;
    class Camera*       mCamera;
    ModelEditor*        mModelEditor;
    ShadersBuilder*     mShadersBuilder;
    ShadersLibrary*     mShadersLibrary;
    LightingCollection* mLightingCollection;
    
    Leap::Controller    mLeapController;
    LeapListener        mleapListener;
    
    Layer*              mLayer;
    LayerRenderer*      mLayerRenderer;
    class InteractionProvider* mInteractionProvider;    
};

}
