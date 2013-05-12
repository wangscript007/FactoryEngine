
#include <Render/LineRenderer.h>
#include <Render/Primitive.h>

namespace ftr {
    
void LineRenderer::Begin(Primitive& primitive)
{
    PrimitiveRenderer::Begin(primitive);
    
    
}
    
void LineRenderer::Render(Primitive& primitive)
{    
    LinePrimitive::Data* data = reinterpret_cast<LinePrimitive::Data*>(primitive.renderData());
    /*
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), &(data->vertices[0].color));
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), data->vertices);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, data->indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    */
    
}

void LineRenderer::End(Primitive& primitive)
{
    PrimitiveRenderer::End(primitive);
}

}
