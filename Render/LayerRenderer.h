
#pragma once

#include <Shading/ShadersInput.h>

namespace ftr {
    
class Layer;
class PrimitiveRenderer;
class Primitive;

//
// Renders layer primitives
//
class LayerRenderer
{
public:
            LayerRenderer(ShadersInput& shadersInput);
    virtual ~LayerRenderer();
    
    virtual void Render(Layer& layer);
    
    
protected:
    void RenderSublayersRecursively(Layer& layer);
    void AddRenderer(PrimitiveRenderer* primitiveRenderer);
    
    virtual void RenderInternal(Layer& layer);
    
    typedef std::vector<PrimitiveRenderer*> RenderersVector;
    RenderersVector mRenderersVector;
    int mDepth;
};

} // ftr