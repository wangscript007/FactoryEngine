
#include <Render/BundleRenderer.h>
#include <Render/Primitive.h>
#include <Render/RenderBundle.h>
#include <Render/LineRenderer.h>
#include <Render/RectangleRenderer.h>

namespace ftr {
    
BundleRenderer::BundleRenderer()
{
    AddRenderer(reinterpret_cast<PrimitiveRenderer*>(new LineRenderer()));
    AddRenderer(reinterpret_cast<RectangleRenderer*>(new RectangleRenderer()));
}
    
void BundleRenderer::AddRenderer(PrimitiveRenderer* primitiveRenderer)
{
    mRenderersVector.push_back(primitiveRenderer);
    
}
    
BundleRenderer::~BundleRenderer()
{
    for(int i = 0; i < mRenderersVector.size(); ++i) {
        FT_DELETE(mRenderersVector[i]);
    }
    mRenderersVector.clear();
}
    
void BundleRenderer::Render(RenderBundle& renderBundle)
{
    RenderBundle::PrimitivesVector primitivesVector;
    for(int i = 0; i < mRenderersVector.size(); ++i) {
        primitivesVector = renderBundle.PrimitivesOfType(mRenderersVector[i]->type());
        mRenderersVector[i]->Begin();
        for (int j = 0; j < primitivesVector.size(); j++) {
            mRenderersVector[i]->Render(*primitivesVector[j]);
        }
        mRenderersVector[i]->End();
    }
    renderBundle.Clear();
}
    
    
} // ftr

