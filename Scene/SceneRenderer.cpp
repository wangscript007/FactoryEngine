
#include <Scene/SceneRenderer.h>

namespace ftr {
    
SceneRenderer::SceneRenderer(ShadingLibrary& shadingLibrary, Camera& camera)
    : LayerRenderer(shadingLibrary.interface()),
    mColorMarkingFramebuffer(NULL),
    mCamera(camera),
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
    mCamera.CreateTransformations();
    RenderToScreen(layer);
    RenderToColorFramebuffer(layer);
}
    
void SceneRenderer::RenderToScreen(Layer &layer)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    mShadingLibrary.UseProgramWithType(ShadingProgram::kMain);
    mCamera.CommitTransformations();
    RenderInternal(layer);
}
    
void SceneRenderer::RenderToColorFramebuffer(Layer &layer)
{
    assert(mColorMarkingFramebuffer);
    mColorMarkingFramebuffer->Bind();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mShadingLibrary.UseProgramWithType(ShadingProgram::kColor);
    mCamera.CommitTransformations();
    LayerRenderer::RenderInternal(layer);
    mColorMarkingFramebuffer->Unbind();
}

void SceneRenderer::setFrame(const  glm::vec4& frame)
{
    mFrame = frame;
    if (mColorMarkingFramebuffer) {
        FT_DELETE(mColorMarkingFramebuffer);
    }
    mColorMarkingFramebuffer = new Framebuffer(glm::vec2(frame[2], frame[3]));
}
    
}

