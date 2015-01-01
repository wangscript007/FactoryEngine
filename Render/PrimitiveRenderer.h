

#pragma once

#include <Shading/ShadingInterface.h>
#include <Render/Batch.h>

namespace ftr {
    
class PrimitiveRenderer
{
public:
    PrimitiveRenderer(ShadingInterface& ShadingInterface) : mShadingInterface(ShadingInterface) {}
    virtual ~PrimitiveRenderer() {}
    
    virtual void Begin(Batch& batch);
    virtual void Render(Batch& batch) = 0;
    virtual void End(Batch& batch);
    
    virtual Primitive::Type type() const { return Primitive::kNone; }
    
protected:
    ShadingInterface mShadingInterface;
};
    
}

