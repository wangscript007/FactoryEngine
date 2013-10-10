
#pragma once

#include <Render/LayerRenderer.h>
#include <Render/Framebuffer.h>
#include <Shading/ShadingLibrary.h>
#include <Scene/Camera.h>

namespace ftr {

class SceneRenderer : public LayerRenderer
{
public:
    SceneRenderer(ShadingLibrary& shadingLibrary, Camera& camera);
    virtual ~SceneRenderer();
    
    void Render(Layer &layer);
    
    void setFrame(const  glm::vec4& frame);
    
    Framebuffer* colorMarkingFramebuffer() const { return mColorMarkingFramebuffer; }
    
private:
    void RenderToScreen(Layer &layer);
    void RenderToColorFramebuffer(Layer &layer);
    
    Framebuffer* mColorMarkingFramebuffer;
     glm::vec4 mFrame;
    ShadingLibrary& mShadingLibrary;
    Camera& mCamera;
};
    
}

