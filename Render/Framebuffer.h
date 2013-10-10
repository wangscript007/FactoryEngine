
#pragma once

namespace ftr {

class Framebuffer
{
public:
    Framebuffer(const glm::vec2& size);
    ~Framebuffer();
    void Bind();
    void Unbind();
    
    glm::vec4 ColorAtPoint(const glm::vec2& point);
    
private:
    GLuint mFramebufferId;
    GLuint mFramebufferTextureId;
    GLuint mRenderbufferId;
};
    
}

