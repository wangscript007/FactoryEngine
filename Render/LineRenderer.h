#pragma once

#include <Render/PrimitiveRenderer.h>

namespace ftr {
    
class LinePrimitive;

class LineRenderer : public PrimitiveRenderer
{
public:
    LineRenderer() {}
    virtual ~LineRenderer() {}
    virtual void Begin();
    virtual void Render(Primitive& primitive);
    virtual void End();
    
    virtual Primitive::Type type() const { return Primitive::kLine; }
};

}

