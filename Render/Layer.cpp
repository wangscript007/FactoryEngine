
#include <Render/Layer.h>
#include <Render/PolygonBatch.h>
#include <Render/LineBatch.h>

namespace ftr {
    
    
Layer::Layer()
    : mDepth(0),
    mParent(NULL),
    mPolygonBatch(new PolygonBatch()),
    mLineBatch(new LineBatch())
{
    
}
    
Layer::~Layer()
{
    FT_DELETE(mPolygonBatch);
    FT_DELETE(mLineBatch);
}
    
void Layer::AddPrimitive(Primitive& primitive)
{
    if (primitive.type() == Primitive::kPolygon) {
        mPolygonBatch->AddPrimitive(primitive);
    }
    if (primitive.type() == Primitive::kLine) {
        mLineBatch->AddPrimitive(primitive);
    }
    else {
        mPrimitivesMap[primitive.type()].push_back(&primitive);
    }
    
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