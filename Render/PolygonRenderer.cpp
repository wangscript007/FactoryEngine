
#include <Render/PolygonRenderer.h>
#include <Render/Primitive.h>

namespace ftr {
    
void PolygonRenderer::Begin(Primitive& primitive)
{
    PrimitiveRenderer::Begin(primitive);
}

void PolygonRenderer::Render(Primitive& primitive)
{
    primitive.renderData(mShadingInterface);
    glBindVertexArray(primitive.vertexArrayObjectId());
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glGetError();
}   

void PolygonRenderer::End(Primitive& primitive)
{
    PrimitiveRenderer::End(primitive);
}
    
}

