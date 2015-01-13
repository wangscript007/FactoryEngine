
#include <Render/PolygonRenderer.h>
#include <Render/Primitive.h>
#include <Render/Batch.h>
#include <Render/PolygonBatch.h>

namespace ftr {
    
void PolygonRenderer::Begin(Batch& batch)
{
    PrimitiveRenderer::Begin(batch);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);
}
    
void PolygonRenderer::Render(Batch& batch)
{
    PolygonBatch& polygonBatch = reinterpret_cast<PolygonBatch&>(batch);
    polygonBatch.CreateRenderData(mShadingInterface);
    assert(!polygonBatch.IsZombie()); // Invalidating polygon during rendering
    GLint count = static_cast<GLint>(polygonBatch.trianglesCount());
    if (count > 0) {
        glBindVertexArray(polygonBatch.vertexArrayObjectId());
        glDrawArrays(GL_TRIANGLES, 0, 3*count);
        glGetError();
    }

}
    
void PolygonRenderer::End(Batch& batch)
{
    PrimitiveRenderer::End(batch);
    
}
    
}

