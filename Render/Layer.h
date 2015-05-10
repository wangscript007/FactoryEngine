
#pragma once

#include <Render/Primitive.h>
#include <Render/BatchBucket.h>

namespace ftr {
    
class PolygonBatch;
class LineBatch;
//
// Gathers primitives data for rendering
//
class Layer
{
public:
    typedef std::vector<Layer*> LayersVector;
    
    Layer();
    virtual ~Layer();
    
    void AddPrimitive(Primitive& primitive);
    void AddSublayer(Layer* layer);
    void RemoveSublayer(Layer* layer);
    BatchBucket::OptionToBatchMap& BatchesWithType(Primitive::Type type);
    void setDepth(int depth);
    const LayersVector& sublayers() { return mSublayers; }
    void Cleanup();
    void Clear();
    
private:
    void OrderSublayers();
    
    LayersVector mSublayers;
    Layer* mParent;
    
    BatchBucket mBatchBucket;
    
    int mDepth;
    
    struct Comparison
    {
        bool operator()(const Layer* a, const Layer* b)
        {
            return a->mDepth < b->mDepth;
        }
    };
    Comparison mComparison;
};

}

