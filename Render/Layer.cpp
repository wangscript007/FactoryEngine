
#include <Render/Layer.h>
#include <Render/PolygonBatch.h>

namespace ftr {
    
    
Layer::Layer()
    : mDepth(0),
    mParent(NULL)
{
    
}
    
Layer::~Layer()
{
}
    
void Layer::AddPrimitive(Primitive& primitive)
{
    mBatchBucket.AddPrimitive(primitive);
}
    
BatchBucket::OptionToBatchMap& Layer::BatchesWithType(Primitive::Type type)
{
    return mBatchBucket.BatchesWithType(type);
}
    
void Layer::Clear()
{
//    mBatchBucket.Clear();
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