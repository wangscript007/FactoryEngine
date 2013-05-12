
#include <Render/LayerRenderer.h>
#include <Render/Primitive.h>
#include <Render/Layer.h>
#include <Render/PointRenderer.h>
#include <Render/LineRenderer.h>
#include <Render/RectangleRenderer.h>
#include <Shading/ShadersInput.h>

namespace ftr {
    
LayerRenderer::LayerRenderer(ShadersInput& shadersInput)
    : mDepth(0)
{
    //AddRenderer(new PointRenderer());
    AddRenderer(new LineRenderer(shadersInput));
    //AddRenderer(new RectangleRenderer());
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
    RenderSublayersRecursively(layer);
    layer.Clear();
}
    
void LayerRenderer::RenderSublayersRecursively(Layer &layer)
{
    Layer::LayersVector sublayers = layer.sublayers();
    for (int i = 0; i < sublayers.size(); ++i) {
        Render(*sublayers[i]);
    }
}
    
    
} // ftr

