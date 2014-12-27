
#include <Render/PolygonRenderer.h>
#include <Render/Primitive.h>

namespace ftr {
    
void PolygonRenderer::Begin(Primitive& primitive)
{
    PrimitiveRenderer::Begin(primitive);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);
 
}

void PolygonRenderer::Render(Primitive& primitive)
{
    PolygonPrimitive& polygonPrimitive = reinterpret_cast<PolygonPrimitive&>(primitive);
    primitive.renderData(mShadingInterface);
    glBindVertexArray(primitive.vertexArrayObjectId());
    GLint count = static_cast<GLint>(polygonPrimitive.GetTriangles().size());
    glDrawArrays(GL_TRIANGLES, 0, 3*count);
    glGetError();
}

void PolygonRenderer::End(Primitive& primitive)
{
    PrimitiveRenderer::End(primitive);
    
}
    
}

