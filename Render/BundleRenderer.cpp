
#include <Render/BundleRenderer.h>
#include <Render/Primitive.h>
#include <Render/RenderBundle.h>

namespace ftr {
    
BundleRenderer::BundleRenderer()
{
    
}
    
BundleRenderer::~BundleRenderer()
{
    /*
    for(auto i = mRendersMap.begin(); i != mRendersMap.end(); ++i) {
        FT_DELETE(i->second);
    }
    mRendersMap.clear();
    */
}
    
void BundleRenderer::Render(RenderBundle& renderBundle)
{
    
}
    
    
} // ftr

