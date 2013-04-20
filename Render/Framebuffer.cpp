
#include <Render/Framebuffer.h>
#include <Render/Primitive.h>

namespace ftr {
    
Framebuffer::Framebuffer()
{
    
}
    
Framebuffer::~Framebuffer()
{
    for(auto i = mRendersMap.begin(); i != mRendersMap.end(); ++i) {
        FT_DELETE(i->second);
    }
    mRendersMap.clear();
}
    
    
} // ftr

