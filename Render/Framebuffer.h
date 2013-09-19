
#pragma once

namespace ftr {

class Framebuffer
{
public:
    Framebuffer(const Vec2& size);
    ~Framebuffer();
    void Bind();
    void Unbind();
    
private:
    GLuint framebufferId;
    GLuint framebufferTextureId;
    GLuint renderbufferId;
};
    
}

