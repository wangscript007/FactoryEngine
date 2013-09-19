
#pragma once

#include <Render/LayerRenderer.h>
#include <Render/Framebuffer.h>

namespace ftr {

class SceneRenderer : public LayerRenderer
{
public:
    SceneRenderer(ShadersInput& shadersInput);
    virtual ~SceneRenderer();
    
    void Render(Layer &layer);
    
    void setFrame(const Frame& frame);
    
private:
    Framebuffer* mColorMarkingFramebuffer;
    Frame mFrame;
};
    
}

