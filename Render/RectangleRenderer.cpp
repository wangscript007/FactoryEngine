#include <Render/RectangleRenderer.h>
#include <Render/Primitive.h>
#include <Main/GLError.h>

namespace ftr {
    
void RectangleRenderer::Begin(Primitive& primitive)
{
    PrimitiveRenderer::Begin(primitive);
}

void RectangleRenderer::Render(Primitive& primitive)
{
    primitive.renderData(mShadersInput);
    glBindVertexArray(primitive.vertexArrayObjectId());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glGetError();
    
}

void RectangleRenderer::End(Primitive& primitive)
{
    PrimitiveRenderer::End(primitive);
}
    
}
