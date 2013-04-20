
#pragma once


namespace ftr {

class Primitive;
    
class Framebuffer
{
public:
             Framebuffer();
    virtual ~Framebuffer();
    
    void Begin();
    void Render(const Primitive& Primitive);
    void End();

private:
    typedef std::unordered_map<int, Primitive*> RenderersMap;
    RenderersMap mRendersMap;
    
};

} // ftr