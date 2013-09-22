
#include <Scene/SceneRenderer.h>

namespace ftr {
    
SceneRenderer::SceneRenderer(ShadingLibrary& shadingLibrary)
    : LayerRenderer(shadingLibrary.interface()),
    mColorMarkingFramebuffer(NULL),
    mShadingLibrary(shadingLibrary)
{
    glClearColor(0.23f,0.23f,0.23f,1.0);
}
    
SceneRenderer::~SceneRenderer()
{
    FT_DELETE(mColorMarkingFramebuffer);
}
    
void SceneRenderer::Render(Layer &layer)
{
    RenderToColorFramebuffer(layer);
    RenderToScreen(layer);
}
    
void SceneRenderer::RenderToScreen(Layer &layer)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mShadingLibrary.UseProgramWithType(ShadingProgram::kMain);
    RenderInternal(layer);
}
    
void SceneRenderer::RenderToColorFramebuffer(Layer &layer)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    assert(mColorMarkingFramebuffer);
    mColorMarkingFramebuffer->Bind();
    mShadingLibrary.UseProgramWithType(ShadingProgram::kMain);
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

