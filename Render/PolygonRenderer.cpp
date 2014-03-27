
#include <Render/PolygonRenderer.h>
#include <Render/Primitive.h>

namespace ftr {
    
void PolygonRenderer::Begin(Primitive& primitive)
{
    PrimitiveRenderer::Begin(primitive);
}

void PolygonRenderer::Render(Primitive& primitive)
{
    PolygonPrimitive& polygonPrimitive = reinterpret_cast<PolygonPrimitive&>(primitive);
    if (polygonPrimitive.mSubpolygons.size()) {
        for (int i = 0; i < polygonPrimitive.mSubpolygons.size(); ++i) {
            PolygonPrimitive* subprimitive = polygonPrimitive.mSubpolygons[i];
            subprimitive->renderData(mShadingInterface);
            glBindVertexArray(subprimitive->vertexArrayObjectId());
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glGetError();
        }
    } else {
        primitive.renderData(mShadingInterface);
        glBindVertexArray(primitive.vertexArrayObjectId());
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glGetError();

    }
    
}

void PolygonRenderer::End(Primitive& primitive)
{
    PrimitiveRenderer::End(primitive);
}
    
}

