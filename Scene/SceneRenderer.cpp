
#include <Scene/SceneRenderer.h>

namespace ftr {
    
SceneRenderer::SceneRenderer(ShadingLibrary& shadingLibrary, Camera& camera)
    : LayerRenderer(shadingLibrary.interface()),
    mColorMarkingFramebuffer(NULL),
    mCamera(camera),
    mShadingLibrary(shadingLibrary)
{
    glClearColor(0.23f,0.23f,0.23f,1.0);
    setMarkingBufferVisible(false);
    
    mProgramTypeForMarkingBuffer = ShadingProgram::kColor;
    mProgramTypeForVisibleBuffer = ShadingProgram::kMain;
}
    
SceneRenderer::~SceneRenderer()
{
    FT_DELETE(mColorMarkingFramebuffer);
}
    
void SceneRenderer::setMarkingBufferVisible(bool visible)
{
    if (visible == mMarkingBufferVisible) return;
    
    mMarkingBufferVisible = visible;
    
    if (mMarkingBufferVisible) {
        mProgramTypeForMarkingBuffer = ShadingProgram::kMain;
        mProgramTypeForVisibleBuffer = ShadingProgram::kColor;
    }
    else {
        mProgramTypeForMarkingBuffer = ShadingProgram::kColor;
        mProgramTypeForVisibleBuffer = ShadingProgram::kMain;
    }
}
    
void SceneRenderer::Render(Layer &layer)
{
    mCamera.CreateTransformations();
    RenderMainContent(layer);
//#ifndef GLES
    RenderMarkingContent(layer);
//#endif
}
    
void SceneRenderer::RenderMainContent(Layer &layer)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    mShadingLibrary.UseProgramWithType(mProgramTypeForVisibleBuffer);
    mCamera.CommitTransformations();
    RenderInternal(layer);
}
    
void SceneRenderer::RenderMarkingContent(Layer &layer)
{
    assert(mColorMarkingFramebuffer);
    mColorMarkingFramebuffer->Bind();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mShadingLibrary.UseProgramWithType(mProgramTypeForMarkingBuffer);
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

