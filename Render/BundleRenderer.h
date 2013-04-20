
#pragma once


namespace ftr {
    
class RenderBundle;
    
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
    
};

} // ftr