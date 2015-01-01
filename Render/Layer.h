
#pragma once

#include <Render/Primitive.h>

namespace ftr {
    
class PolygonBatch;
class LineBatch;
//
// Gathers primitives data for rendering
//
class Layer
{
public:
    typedef std::vector<Primitive*> PrimitivesVector;
    typedef std::vector<Layer*> LayersVector;
    
    Layer();
    virtual ~Layer();
    
    void AddPrimitive(Primitive& primitive);
    void Clear();
    void AddSublayer(Layer* layer);
    void RemoveSublayer(Layer* layer);
    PrimitivesVector& PrimitivesOfType(Primitive::Type type);
    void setDepth(int depth);
    const LayersVector& sublayers() { return mSublayers; }
    PolygonBatch* mPolygonBatch;
    LineBatch* mLineBatch;
    
private:
    typedef std::unordered_map<int, PrimitivesVector> PrimitivesMap;
    void OrderSublayers();
    
    PrimitivesMap mPrimitivesMap;
    LayersVector mSublayers;
    Layer* mParent;
    
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

