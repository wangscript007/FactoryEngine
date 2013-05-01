
#pragma once

#include <Render/PrimitiveRenderer.h>

namespace ftr {
    
class RectanglePrimitive;

class RectangleRenderer : public PrimitiveRenderer
{
public:
    RectangleRenderer() {}
    virtual ~RectangleRenderer() {}
    virtual void Begin(Primitive& primitive);
    virtual void Render(Primitive& primitive);
    virtual void End(Primitive& primitive);
    
    virtual Primitive::Type type() const { return Primitive::kRectangle; }
};
    
}

