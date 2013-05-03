
#include <Render/PointRenderer.h>
#include <Render/Primitive.h>

namespace ftr {
    
void PointRenderer::Begin(Primitive& primitive)
{
    PrimitiveRenderer::Begin(primitive);
    glEnable(GL_POINT_SMOOTH);
}

void PointRenderer::Render(Primitive& primitive)
{
    PointPrimitive::Data* data = reinterpret_cast<PointPrimitive::Data*>(primitive.renderData());
    glPointSize(3.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), &(data->vertices[0].color));
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), data->vertices);
    glDrawElements(GL_POINTS, 1, GL_UNSIGNED_BYTE, data->indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void PointRenderer::End(Primitive& primitive)
{
    PrimitiveRenderer::End(primitive);
    glDisable(GL_POINT_SMOOTH);
}
    
}
