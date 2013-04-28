
#include <Render/RenderBundle.h>

namespace ftr {
    
void RenderBundle::AddPrimitive(Primitive& primitive)
{
    mPrimitivesMap[primitive.type()].push_back(&primitive);
}
    
RenderBundle::PrimitivesVector& RenderBundle::PrimitivesOfType(Primitive::Type type)
{
    return mPrimitivesMap[static_cast<int>(type)];
}
    
void RenderBundle::Clear()
{
    mPrimitivesMap.clear();
}
    
}