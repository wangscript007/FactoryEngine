#include <Render/RectangleRenderer.h>
#include <Render/Primitive.h>
#include <Main/GLError.h>

namespace ftr {
    
void RectangleRenderer::Begin(Primitive& primitive)
{
    //PrimitiveRenderer::Begin(primitive);
}

void RectangleRenderer::Render(Primitive& primitive)
{
    RectanglePrimitive::Data* data = reinterpret_cast<RectanglePrimitive::Data*>(primitive.renderData());
    /*
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), data->vertices);
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), &(data->vertices[0].color));
    glNormalPointer(GL_FLOAT, sizeof(Vertex), &(data->vertices[0].normal));
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, data->indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
     */
    
    assert(primitive.vertexBufferId() > 0);
    glBindBuffer(GL_ARRAY_BUFFER, primitive.vertexBufferId());
    GetError();
    glEnableVertexAttribArray(0);
    GetError();
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    GetError();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    GetError();
    glDisableVertexAttribArray(0);
    GetError();
    
}

void RectangleRenderer::End(Primitive& primitive)
{
    //PrimitiveRenderer::End(primitive);
}
    
}
