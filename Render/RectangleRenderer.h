
#pragma once

#include <Render/PrimitiveRenderer.h>

namespace ftr {
    
class RectanglePrimitive;

class RectangleRenderer : public PrimitiveRenderer
{
public:
    RectangleRenderer() {}
    virtual ~RectangleRenderer() {}
    virtual void Begin();
    virtual void Render(Primitive& primitive);
    virtual void End();
    
    virtual Primitive::Type type() const { return Primitive::kRectangle; }
};
    
}

