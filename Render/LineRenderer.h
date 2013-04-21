#pragma once

#include <Render/PrimitiveRenderer.h>

namespace ftr {
    
class LinePrimitive;

class LineRenderer : public PrimitiveRenderer
{
public:
    LineRenderer();
    virtual ~LineRenderer() {}
    virtual void Begin();
    virtual void Render(LinePrimitive& primitive);
    virtual void End();
};

}

