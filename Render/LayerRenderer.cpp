
#include <Render/LayerRenderer.h>
#include <Render/Primitive.h>
#include <Render/Layer.h>
#include <Render/PointRenderer.h>
#include <Render/LineRenderer.h>
#include <Render/PolygonRenderer.h>
#include <Render/PolygonBatch.h>
#include <Render/LineBatch.h>
#include <Render/BatchBucket.h>
#include <Shading/ShadingInterface.h>

namespace ftr {
    
LayerRenderer::LayerRenderer(ShadingInterface& shadingInterface)
    : mDepth(0)
{
    mRenderLines = true;
    AddRenderer(new PolygonRenderer(shadingInterface));
    AddRenderer(new LineRenderer(shadingInterface));
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
    RenderInternal(layer);
}
    
void LayerRenderer::RenderInternal(Layer& layer)
{
    for(auto& renderer : mRenderersVector) {
        if ((renderer->type() != Primitive::kLine) || mRenderLines) {
            BatchBucket::OptionToBatchMap &batches = layer.BatchesWithType(renderer->type());
            for (auto& pair : batches)
            {
                BatchBucket::BatchVector& batchVector = pair.second;
                for (auto& batch : batchVector) {
                    renderer->Begin(*batch);
                    renderer->Render(*batch);
                    renderer->End(*batch);
                }
            }
        }
    }
        
    RenderSublayersRecursively(layer);
}
    
void LayerRenderer::RenderSublayersRecursively(Layer &layer)
{
    Layer::LayersVector sublayers = layer.sublayers();
    for (int i = 0; i < sublayers.size(); ++i) {
        RenderInternal(*sublayers[i]);
    }
}
    
    
} // ftr

