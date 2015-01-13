
#include <Render/PrimitiveRenderer.h>
#include <Main/GLError.h>

namespace ftr {
    
void PrimitiveRenderer::Begin(Batch& batch)
{
    mShadingInterface.SetLightingOn(batch.option(Primitive::kUseLighting));

    if (batch.option(Primitive::kUseDepth)) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
    if (batch.option(Primitive::kUseBlend)) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        glDisable(GL_BLEND);
    }
}
    
void PrimitiveRenderer::End(Batch& batch)
{
}

}