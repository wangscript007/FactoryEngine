
#include <Render/LineRenderer.h>
#include <Render/Primitive.h>

namespace ftr {
    
void LineRenderer::Begin()
{
    glEnableClientState(GL_VERTEX_ARRAY);
}
    
void LineRenderer::Render(Primitive& primitive)
{
    if (primitive.isInvalid()) return;
    
    LinePrimitive::Data* data = reinterpret_cast<LinePrimitive::Data*>(primitive.renderData());
    
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), data->vertices);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, data->indices);
}

void LineRenderer::End()
{
    glDisableClientState(GL_VERTEX_ARRAY);
}

}
