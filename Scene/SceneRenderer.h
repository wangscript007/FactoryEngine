
#pragma once

#include <Render/LayerRenderer.h>
#include <Render/Framebuffer.h>
#include <Shading/ShadingLibrary.h>

namespace ftr {

class SceneRenderer : public LayerRenderer
{
public:
    SceneRenderer(ShadingLibrary& shadingLibrary);
    virtual ~SceneRenderer();
    
    void Render(Layer &layer);
    
    void setFrame(const Frame& frame);
    
private:
    void RenderToScreen(Layer &layer);
    void RenderToColorFramebuffer(Layer &layer);
    
    Framebuffer* mColorMarkingFramebuffer;
    Frame mFrame;
    ShadingLibrary& mShadingLibrary;
};
    
}

