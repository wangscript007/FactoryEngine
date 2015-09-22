
#include <Render/LineRenderer.h>
#include <Render/Primitive.h>
#include <Render/LineBatch.h>

namespace ftr {
    
void LineRenderer::Begin(Batch& batch)
{
    PrimitiveRenderer::Begin(batch);
}
    
void LineRenderer::Render(Batch& batch)
{
    LineBatch& lineBatch = reinterpret_cast<LineBatch&>(batch);
    lineBatch.CreateRenderData(mShadingInterface);
    assert(!lineBatch.IsZombie()); // Invalidating line during rendering
    if (lineBatch.size()) {
    }
}


void LineRenderer::End(Batch& batch)
{
    PrimitiveRenderer::End(batch);
 
}

}
