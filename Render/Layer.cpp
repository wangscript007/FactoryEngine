
#include <Render/Layer.h>

namespace ftr {
    
Layer::Layer()
    : mDepth(0)
{
    
}
    
void Layer::AddPrimitive(Primitive& primitive)
{
    mPrimitivesMap[primitive.type()].push_back(&primitive);
}
    
Layer::PrimitivesVector& Layer::PrimitivesOfType(Primitive::Type type)
{
    return mPrimitivesMap[static_cast<int>(type)];
}
    
void Layer::Clear()
{
    mPrimitivesMap.clear();
}
    
void Layer::AddSublayer(Layer* layer)
{

}
    
void Layer::RemoveSublayer(Layer* layer)
{
    
}
    
void Layer::setDepth(int depth)
{
    
}
    
}