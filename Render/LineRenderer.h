#pragma once

#include <Render/PrimitiveRenderer.h>

namespace ftr {
    
class LinePrimitive;
class LineBatch;

class LineRenderer : public PrimitiveRenderer
{
public:
    LineRenderer(ShadingInterface& ShadingInterface) : PrimitiveRenderer(ShadingInterface) {}
    virtual ~LineRenderer() {}
    virtual void Begin(Primitive& primitive);
    virtual void Render(Primitive& primitive);
    virtual void RenderBatch(LineBatch& lineBatch);
    virtual void End(Primitive& primitive);
    
    virtual Primitive::Type type() const { return Primitive::kLine; }
};

}

