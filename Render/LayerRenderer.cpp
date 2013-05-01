
#include <Render/LayerRenderer.h>
#include <Render/Primitive.h>
#include <Render/Layer.h>
#include <Render/LineRenderer.h>
#include <Render/RectangleRenderer.h>

namespace ftr {
    
LayerRenderer::LayerRenderer()
    : mDepth(0)
{
    AddRenderer(reinterpret_cast<PrimitiveRenderer*>(new LineRenderer()));
    AddRenderer(reinterpret_cast<RectangleRenderer*>(new RectangleRenderer()));
}
    
void LayerRenderer::AddRenderer(PrimitiveRenderer* primitiveRenderer)
{
    mRenderersVector.push_back(primitiveRenderer);
    
}
    
LayerRenderer::~LayerRenderer()
{
    for(int i = 0; i < mRenderersVector.size(); ++i) {
        FT_DELETE(mRenderersVector[i]);
    }
    mRenderersVector.clear();
}
    
void LayerRenderer::Render(Layer& layer)
{
    Layer::PrimitivesVector primitivesVector;
    for(int i = 0; i < mRenderersVector.size(); ++i) {
        primitivesVector = layer.PrimitivesOfType(mRenderersVector[i]->type());
        for (int j = 0; j < primitivesVector.size(); j++) {
            mRenderersVector[i]->Begin(*primitivesVector[j]);
            mRenderersVector[i]->Render(*primitivesVector[j]);
            mRenderersVector[i]->End(*primitivesVector[j]);
        }
        
    }
    layer.Clear();
}
    
    
} // ftr

