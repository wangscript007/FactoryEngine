#pragma once

#include <Render/PrimitiveRenderer.h>
#include <Render/Batch.h>

namespace ftr {
    
class LinePrimitive;

class LineRenderer : public PrimitiveRenderer
{
public:
    LineRenderer(ShadingInterface& ShadingInterface) : PrimitiveRenderer(ShadingInterface) {}
    virtual ~LineRenderer() {}
    virtual void Begin(Batch& batch);
    virtual void Render(Batch& batch);
    virtual void End(Batch& batch);
    
    virtual Primitive::Type type() const { return Primitive::kLine; }
};

}

