
#include "RenderBundle.h"

namespace ftr {
    
void RenderBundle::AddPrimitive(Primitive& primitive)
{
    mPrimitivesMap[primitive.type()].push_back(&primitive);
}
    
}