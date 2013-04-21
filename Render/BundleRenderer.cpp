
#include <Render/BundleRenderer.h>
#include <Render/Primitive.h>
#include <Render/RenderBundle.h>
#include <Render/LineRenderer.h>

namespace ftr {
    
BundleRenderer::BundleRenderer()
{
    AddRenderer(reinterpret_cast<PrimitiveRenderer*>(new LineRenderer()));
}
    
void BundleRenderer::AddRenderer(PrimitiveRenderer* primitiveRenderer)
{
    mRenderersMap[primitiveRenderer->type()] = primitiveRenderer;
}
    
BundleRenderer::~BundleRenderer()
{
    for(auto i = mRenderersMap.begin(); i != mRenderersMap.end(); ++i) {
        FT_DELETE(i->second);
    }
    mRenderersMap.clear();
}
    
void BundleRenderer::Render(RenderBundle& renderBundle)
{
    
}
    
    
} // ftr

