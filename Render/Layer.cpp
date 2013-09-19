
#include <Render/Layer.h>

namespace ftr {
    
Layer::Layer()
    : mDepth(0),
    mParent(NULL)
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
    for (int i = 0; i < mSublayers.size(); ++i) {
        mSublayers[i]->Clear();
    }
}
    
void Layer::AddSublayer(Layer* layer)
{
    mSublayers.push_back(layer);
    OrderSublayers();
}
    
void Layer::RemoveSublayer(Layer* layer)
{
    auto it = std::find(mSublayers.begin(), mSublayers.end(), layer);
    if (it != mSublayers.end()) {
        mSublayers.erase(it);
    }
}
    
void Layer::setDepth(int depth)
{
    mDepth = depth;
    if (mParent) {
        mParent->OrderSublayers();
    }
}
    
void Layer::OrderSublayers()
{
    std::sort(mSublayers.begin(), mSublayers.end(), mComparison);
}
    
}