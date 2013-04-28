
#pragma once

#include <Render/PrimitiveRenderer.h>

namespace ftr {

class PolygonRenderer : public PrimitiveRenderer
{
public:
    PolygonRenderer() {}
    virtual ~PolygonRenderer() {}
    virtual void Begin();
    virtual void Render(Primitive& primitive);
    virtual void End();
    
    virtual Primitive::Type type() const { return Primitive::kPolygon; }
};
    
}

