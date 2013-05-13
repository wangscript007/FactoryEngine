
#include <Render/PrimitiveRenderer.h>
#include <Main/GLError.h>

namespace ftr {
    
void PrimitiveRenderer::Begin(Primitive& primitive)
{
    if (primitive.option(Primitive::kUseLighting)) {
        
    }
    if (primitive.option(Primitive::kUseDepth)) {
        glEnable(GL_DEPTH_TEST);
    }
    if (primitive.option(Primitive::kUseBlend)) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
}
    
void PrimitiveRenderer::End(Primitive& primitive)
{
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

}