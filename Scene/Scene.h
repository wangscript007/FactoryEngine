//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//
#pragma once

#include <Processing/ModelEditor.h>
#include <Interaction/InteractionProvider.h>
#include <Leap/LeapListener.h>
#include <Scene/SceneRenderer.h>


namespace ftr {

class Layer;
class LayerRenderer;
class Viewport;
class Camera;
class ShadingLibrary;
class Workspace;
class LightingCollection;
class Picker;
    
class Scene
{
public:
    
    enum Option {
        kOptionShowNone           = 0,
        kOptionShowMarkingView    = 1 << 1,
        kOptionShowOctree         = 1 << 2
    };

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
    unsigned long     Size() { return mModelEditor->Size(); }
    
    InteractionProvider* InteractionProvider() const { return mInteractionProvider; }
    Camera*             Camera() const { return mCamera; }
    void                Step(float dTime);
    float               FPS() const { return mFPS; }
    
    Framebuffer*        colorMarkingFramebuffer() const { return mSceneRenderer->colorMarkingFramebuffer(); }
    const Viewport&     viewport() const { return mViewport; }
    

    
    void setOption(Option option, bool value);
    bool option(Option option) const { return (mOptions & static_cast<unsigned int>(option)) != 0; }
    
private:
    unsigned int        mOptions;
    
    Workspace*          mWorkspace;
    ftr::Camera*        mCamera;
    ModelEditor*        mModelEditor;
    ShadingLibrary*     mShadingLibrary;
    LightingCollection* mLightingCollection;
    Viewport            mViewport;
    Picker*             mPicker;
    
    
    Leap::Controller    mLeapController;
    LeapListener        mleapListener;
    
    Layer*              mLayer;
    SceneRenderer*      mSceneRenderer;
    ftr::InteractionProvider* mInteractionProvider;
    
    float mFPS;
    int mFramesCount;
};

}
