
#include <Render/LineRenderer.h>
#include <Render/Primitive.h>
#include <Render/LineBatch.h>

namespace ftr {
    
void LineRenderer::Begin(Primitive& primitive)
{
    PrimitiveRenderer::Begin(primitive);
}
    
void LineRenderer::Render(Primitive& primitive)
{    
    primitive.UpdateRenderData(mShadingInterface);
    glBindVertexArray(primitive.vertexArrayObjectId());
    glDrawArrays(GL_LINES, 0, 2);
    glGetError();
}
    
void LineRenderer::RenderBatch(LineBatch& lineBatch)
{
    lineBatch.UpdateRenderData(mShadingInterface);
    glBindVertexArray(lineBatch.vertexArrayObjectId());
    glDrawArrays(GL_LINES, 0, 2*lineBatch.size());
    glGetError();
}


void LineRenderer::End(Primitive& primitive)
{
    PrimitiveRenderer::End(primitive);
 
}

}
