
#include <Render/PolygonRenderer.h>
#include <Render/Primitive.h>

namespace ftr {
    
void PolygonRenderer::Begin()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glDepthMask(GL_TRUE);
}

void PolygonRenderer::Render(Primitive& primitive)
{
    PolygonPrimitive::Data* data = reinterpret_cast<PolygonPrimitive::Data*>(primitive.renderData());
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), &(data->vertices[0].color));
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), data->vertices);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, data->indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}   

void PolygonRenderer::End()
{
    
}
    
}

