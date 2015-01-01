#pragma once

#include <Render/PrimitiveRenderer.h>
#include <Render/Batch.h>

namespace ftr {
    
class PointPrimitive;

class PointRenderer : public PrimitiveRenderer
{
public:
    virtual ~PointRenderer() {}
    virtual void Begin(Batch& batch);
    virtual void Render(Batch& batch);
    virtual void End(Batch& batch);
    
    virtual Primitive::Type type() const { return Primitive::kPoint; }
};
    
}

