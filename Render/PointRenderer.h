#pragma once

#include <Render/PrimitiveRenderer.h>

namespace ftr {
    
class PointPrimitive;

class PointRenderer : public PrimitiveRenderer
{
public:
    PointRenderer() {}
    virtual ~PointRenderer() {}
    virtual void Begin(Primitive& primitive);
    virtual void Render(Primitive& primitive);
    virtual void End(Primitive& primitive);
    
    virtual Primitive::Type type() const { return Primitive::kPoint; }
};
    
}

