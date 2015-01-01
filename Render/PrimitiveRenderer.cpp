
#include <Render/PrimitiveRenderer.h>
#include <Main/GLError.h>

namespace ftr {
    
void PrimitiveRenderer::Begin(Batch& batch)
{
    if (batch.option(Primitive::kUseLighting)) {
        
    }
    if (batch.option(Primitive::kUseDepth)) {
        glEnable(GL_DEPTH_TEST);
    }
    if (batch.option(Primitive::kUseBlend)) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}
    
void PrimitiveRenderer::End(Batch& batch)
{
    glDisable(GL_DEPTH_TEST);
}

}