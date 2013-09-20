
#include <Render/PolygonRenderer.h>
#include <Render/Primitive.h>

namespace ftr {
    
void PolygonRenderer::Begin(Primitive& primitive)
{
    PrimitiveRenderer::Begin(primitive);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}

void PolygonRenderer::Render(Primitive& primitive)
{
    PolygonPrimitive::Data* data = reinterpret_cast<PolygonPrimitive::Data*>(primitive.renderData(mShadingInterface));
    
}   

void PolygonRenderer::End(Primitive& primitive)
{
    PrimitiveRenderer::End(primitive);
}
    
}

