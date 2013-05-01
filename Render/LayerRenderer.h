
#pragma once


namespace ftr {
    
class Layer;
class PrimitiveRenderer;
    
class Primitive;
//
// Renders budle of primitives
//
class LayerRenderer
{
public:
             LayerRenderer();
    virtual ~LayerRenderer();
    
    void Render(Layer& layer);
    
    
private:
    void AddRenderer(PrimitiveRenderer* primitiveRenderer);
    
    typedef std::vector<PrimitiveRenderer*> RenderersVector;
    RenderersVector mRenderersVector;
    int mDepth;
};

} // ftr