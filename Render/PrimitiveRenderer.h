

#pragma once

#include <Render/Primitive.h>

namespace ftr {

class PrimitiveRenderer
{
public:
    PrimitiveRenderer() {}
    virtual ~PrimitiveRenderer() {}
    
    virtual void Begin() = 0;
    virtual void Render(Primitive& primitive) = 0;
    virtual void End() = 0;
    
    virtual Primitive::Type type() const { return Primitive::kNone; }
};
    
}

