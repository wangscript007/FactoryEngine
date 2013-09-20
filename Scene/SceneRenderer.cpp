
#include "SceneRenderer.h"

namespace ftr {
    
SceneRenderer::SceneRenderer(ShadingInterface& ShadingInterface)
    : LayerRenderer(ShadingInterface),
    mColorMarkingFramebuffer(NULL)
{
    glClearColor(0.23f,0.23f,0.23f,1.0);
}
    
SceneRenderer::~SceneRenderer()
{
    FT_DELETE(mColorMarkingFramebuffer);
}
    
void SceneRenderer::Render(Layer &layer)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    RenderInternal(layer);
    assert(mColorMarkingFramebuffer);
    mColorMarkingFramebuffer->Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    LayerRenderer::RenderInternal(layer);
    mColorMarkingFramebuffer->Unbind();
}
    
void SceneRenderer::setFrame(const Frame& frame)
{
    mFrame = frame;
    if (mColorMarkingFramebuffer) {
        FT_DELETE(mColorMarkingFramebuffer);
    }
    mColorMarkingFramebuffer = new Framebuffer(mFrame.mMax);
}
    
}

