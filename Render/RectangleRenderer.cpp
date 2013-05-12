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
    
}

void RectangleRenderer::End(Primitive& primitive)
{
    //PrimitiveRenderer::End(primitive);
}
    
}
