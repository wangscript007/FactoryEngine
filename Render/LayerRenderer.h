
#pragma once


namespace ftr {
    
class Layer;
class PrimitiveRenderer;
class Primitive;
class ShadersInput;
//
// Renders layer primitives
//
class LayerRenderer
{
public:
             LayerRenderer(ShadersInput& shadersInput);
    virtual ~LayerRenderer();
    
    void Render(Layer& layer);
    
    
private:
    void RenderSublayersRecursively(Layer& layer);
    void AddRenderer(PrimitiveRenderer* primitiveRenderer);
    
    typedef std::vector<PrimitiveRenderer*> RenderersVector;
    RenderersVector mRenderersVector;
    int mDepth;
};

} // ftr