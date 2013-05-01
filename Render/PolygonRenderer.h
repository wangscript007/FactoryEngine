
#pragma once

#include <Render/PrimitiveRenderer.h>

namespace ftr {

class PolygonRenderer : public PrimitiveRenderer
{
public:
    PolygonRenderer() {}
    virtual ~PolygonRenderer() {}
    virtual void Begin(Primitive& primitive);
    virtual void Render(Primitive& primitive);
    virtual void End(Primitive& primitive);
    
    virtual Primitive::Type type() const { return Primitive::kPolygon; }
};
    
}

