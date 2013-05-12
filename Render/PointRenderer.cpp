
#include <Render/PointRenderer.h>
#include <Render/Primitive.h>

namespace ftr {
    
void PointRenderer::Begin(Primitive& primitive)
{
    PrimitiveRenderer::Begin(primitive);
    
}

void PointRenderer::Render(Primitive& primitive)
{
    PointPrimitive::Data* data = reinterpret_cast<PointPrimitive::Data*>(primitive.renderData(mShadersInput));
    
}

void PointRenderer::End(Primitive& primitive)
{
    PrimitiveRenderer::End(primitive);

}
    
}
