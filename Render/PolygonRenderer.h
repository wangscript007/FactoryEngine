
#pragma once

#include <Render/PrimitiveRenderer.h>
#include <Render/Batch.h>

namespace ftr {
    
class Batch;

class PolygonRenderer : public PrimitiveRenderer
{
public:
    PolygonRenderer(ShadingInterface& ShadingInterface) : PrimitiveRenderer(ShadingInterface) {}
    virtual ~PolygonRenderer() {}
    virtual void Begin(Batch& primitive);
    virtual void Render(Batch& batch);
    virtual void End(Batch& primitive);
    
    virtual Primitive::Type type() const { return Primitive::kPolygon; }
};
    
}

