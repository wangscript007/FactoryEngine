
#include <Render/PrimitiveRenderer.h>

namespace ftr {
    
void PrimitiveRenderer::Begin(Primitive& primitive)
{
    
    if (primitive.option(Primitive::kUseLighting)) {
        glEnable(GL_LIGHTING);
    }
    if (primitive.option(Primitive::kUseDepth)) {
        glEnable(GL_DEPTH);
        glEnable(GL_DEPTH_TEST);
    }
    if (primitive.option(Primitive::kUseBlend)) {
        glEnable(GL_BLEND);
    } else {
        
    }
}
    
void PrimitiveRenderer::End(Primitive& primitive)
{
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH);
    glDisable(GL_DEPTH_TEST);
}

    
}
