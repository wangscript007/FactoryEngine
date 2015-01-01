
#include <Render/PointRenderer.h>

namespace ftr {
    
void PointRenderer::Begin(Batch& batch)
{
    PrimitiveRenderer::Begin(batch);
    
}

void PointRenderer::Render(Batch& batch)
{
    //PointPrimitive::Data* data = reinterpret_cast<PointPrimitive::Data*>(primitive.renderData(mShadingInterface));
    
}

void PointRenderer::End(Batch& batch)
{
    PrimitiveRenderer::End(batch);

}
    
}
