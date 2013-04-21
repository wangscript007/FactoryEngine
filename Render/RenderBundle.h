
#pragma once

#include <Render/Primitive.h>

namespace ftr {
//
// Gathers primitives data for rendering
//
class RenderBundle
{
public:
    typedef std::vector<Primitive*> PrimitivesVector;
    
    virtual ~RenderBundle() {}
    
    void AddPrimitive(Primitive& primitive);
    PrimitivesVector& PrimitivesOfType(Primitive::Type type);
    
private:
    
    typedef std::unordered_map<int, PrimitivesVector> PrimitivesMap;
    
    PrimitivesMap mPrimitivesMap;
};

}

