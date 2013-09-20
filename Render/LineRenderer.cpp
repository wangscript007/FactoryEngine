
#include <Render/LineRenderer.h>
#include <Render/Primitive.h>

namespace ftr {
    
void LineRenderer::Begin(Primitive& primitive)
{
    PrimitiveRenderer::Begin(primitive);
    
    
}
    
void LineRenderer::Render(Primitive& primitive)
{    
    primitive.renderData(mShadingInterface);
    glBindVertexArray(primitive.vertexArrayObjectId());
    glDrawArrays(GL_LINES, 0, 2);
    glGetError();
}

void LineRenderer::End(Primitive& primitive)
{
    PrimitiveRenderer::End(primitive);
}

}
