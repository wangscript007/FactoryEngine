

#pragma once

#include <Render/Primitive.h>
#include <Shading/ShadersInput.h>

namespace ftr {

class PrimitiveRenderer
{
public:
    PrimitiveRenderer(ShadersInput& shadersInput) : mShadersInput(shadersInput) {}
    virtual ~PrimitiveRenderer() {}
    
    virtual void Begin(Primitive& primitive);
    virtual void Render(Primitive& primitive) = 0;
    virtual void End(Primitive& primitive);
    
    virtual Primitive::Type type() const { return Primitive::kNone; }
    
protected:
    ShadersInput mShadersInput;
};
    
}

