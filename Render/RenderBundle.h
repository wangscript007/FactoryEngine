
#pragma once

#include <Render/Primitive.h>

namespace ftr {
//
// Gathers primitives data for rendering
//
class RenderBundle
{
public:
    virtual ~RenderBundle() {}
    
    void AddPrimitive(Primitive& primitive);
private:
    typedef std::vector<Primitive*> PrimitivesVector;
    typedef std::unordered_map<int, PrimitivesVector> PrimitivesMap;
    
    PrimitivesMap mPrimitivesMap;
};

}

