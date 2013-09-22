
#pragma once

namespace ftr {

class Framebuffer
{
public:
    Framebuffer(const Vec2& size);
    ~Framebuffer();
    void Bind();
    void Unbind();
    
    Color4f ColorAtPoint(const Vec2& point);
    
private:
    GLuint mFramebufferId;
    GLuint mFramebufferTextureId;
    GLuint mRenderbufferId;
};
    
}

