
#pragma once

#include <Render/Primitive.h>

namespace ftr {
//
// Gathers primitives data for rendering
//
class Layer
{
public:
    typedef std::vector<Primitive*> PrimitivesVector;
    typedef std::vector<Layer*> LayersVector;
    
    Layer();
    virtual ~Layer() {}
    
    void AddPrimitive(Primitive& primitive);
    void Clear();
    void AddSublayer(Layer* layer);
    void RemoveSublayer(Layer* layer);
    PrimitivesVector& PrimitivesOfType(Primitive::Type type);
    void setDepth(int depth);
    
private:
    
    typedef std::unordered_map<int, PrimitivesVector> PrimitivesMap;
    
    PrimitivesMap mPrimitivesMap;
    LayersVector mSublayers;
    Layer* mParent;
    int mDepth;
};

}

