
#include <Render/LayerRenderer.h>
#include <Render/Primitive.h>
#include <Render/Layer.h>
#include <Render/PointRenderer.h>
#include <Render/LineRenderer.h>
#include <Render/PolygonRenderer.h>
#include <Render/PolygonBatch.h>
#include <Render/LineBatch.h>
#include <Shading/ShadingInterface.h>

namespace ftr {
    
LayerRenderer::LayerRenderer(ShadingInterface& shadingInterface)
    : mDepth(0)
{
    //AddRenderer(new PointRenderer());
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
    Layer::PrimitivesVector primitivesVector;
    for(int i = 0; i < mRenderersVector.size(); ++i) {
        primitivesVector = layer.PrimitivesOfType(mRenderersVector[i]->type());
        if (mRenderersVector[i]->type() == Primitive::kPolygon) {
            if (layer.mPolygonBatch->size()) {
                glEnable(GL_DEPTH_TEST);
                PolygonRenderer* polygonRenderer = reinterpret_cast<PolygonRenderer*>(mRenderersVector[i]);
                polygonRenderer->RenderBatch(*layer.mPolygonBatch);

            }
        }
        else if (mRenderersVector[i]->type() == Primitive::kLine) {
            if (layer.mLineBatch->size()) {
                LineRenderer* lineRenderer = reinterpret_cast<LineRenderer*>(mRenderersVector[i]);
                lineRenderer->RenderBatch(*layer.mLineBatch);
                
            }
        }
        else {
            for (int j = 0; j < primitivesVector.size(); j++) {
                mRenderersVector[i]->Begin(*primitivesVector[j]);
                mRenderersVector[i]->Render(*primitivesVector[j]);
                mRenderersVector[i]->End(*primitivesVector[j]);
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

