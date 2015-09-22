
#include <Scene/SceneRenderer.h>

namespace ftr {
    
SceneRenderer::SceneRenderer(Camera& camera)
    : LayerRenderer(*(new ShadingInterface())),
    mCamera(camera)
{
    setMarkingBufferVisible(false);
    
//    mProgramTypeForMarkingBuffer = ShadingProgram::kColor;
//    mProgramTypeForVisibleBuffer = ShadingProgram::kMain;
}
    
SceneRenderer::~SceneRenderer()
{
}
    
void SceneRenderer::setMarkingBufferVisible(bool visible)
{
    if (visible == mMarkingBufferVisible) return;
    
    mMarkingBufferVisible = visible;
    
//    if (mMarkingBufferVisible) {
//        mProgramTypeForMarkingBuffer = ShadingProgram::kMain;
//        mProgramTypeForVisibleBuffer = ShadingProgram::kColor;
//    }
//    else {
//        mProgramTypeForMarkingBuffer = ShadingProgram::kColor;
//        mProgramTypeForVisibleBuffer = ShadingProgram::kMain;
//    }
}
    
void SceneRenderer::Render(Layer &layer)
{
    mCamera.CreateTransformations();
    RenderMainContent(layer);
}
    
void SceneRenderer::RenderMainContent(Layer &layer)
{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    mShadingLibrary.UseProgramWithType(mProgramTypeForVisibleBuffer);
//    mCamera.CommitTransformations();
//    mRenderLines = mProgramTypeForVisibleBuffer != ShadingProgram::kColor;
//    RenderInternal(layer);
}
    
void SceneRenderer::RenderMarkingContent(Layer &layer)
{
    
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    mShadingLibrary.UseProgramWithType(mProgramTypeForMarkingBuffer);
//    mCamera.CommitTransformations();
//    mRenderLines = mProgramTypeForMarkingBuffer != ShadingProgram::kColor;
//    LayerRenderer::RenderInternal(layer);
    
}

void SceneRenderer::setFrame(const  glm::vec4& frame)
{
    mFrame = frame;
}
    
}

