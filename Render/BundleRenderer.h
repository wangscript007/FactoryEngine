
#pragma once


namespace ftr {
    
class RenderBundle;
class PrimitiveRenderer;
    
class Primitive;
//
// Renders budle of primitives
//
class BundleRenderer
{
public:
             BundleRenderer();
    virtual ~BundleRenderer();
    
    void Render(RenderBundle& renderBundle);
    
    
private:
    void AddRenderer(PrimitiveRenderer* primitiveRenderer);
    
    typedef std::unordered_map<int, PrimitiveRenderer*> RenderersMap;
    RenderersMap mRenderersMap;
};

} // ftr