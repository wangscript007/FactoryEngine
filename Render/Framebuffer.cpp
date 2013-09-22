
#include <Render/Framebuffer.h>

namespace ftr {

Framebuffer::Framebuffer(const Vec2& size)
{
    // create framebuffer
    glGenFramebuffers(1, &mFramebufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferId);
    
    // attach renderbuffer to fb so that depth-sorting works
    glGenRenderbuffers(1, &mRenderbufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, mRenderbufferId);
    glRenderbufferStorage(GL_RENDERBUFFER,
                          GL_DEPTH_COMPONENT,
                          size.mX,
                          size.mY);
    
    // create texture to use for rendering second pass
    glGenTextures (1, &mFramebufferTextureId);
    glBindTexture (GL_TEXTURE_2D, mFramebufferTextureId);
    // make the texture the same size as the viewport
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 size.mX,
                 size.mY,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 NULL);
	
    // attach render buffer (depth) and texture (colour) to fb
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER,
                              mRenderbufferId);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D,
                           mFramebufferTextureId,
                           0);
    // redirect fragment shader output 0 used to the texture that we just bound
    GLenum draw_bufs[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers (1, draw_bufs);
    
    Unbind();
}
    
Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &mFramebufferId);
    glDeleteTextures(1, &mFramebufferTextureId);
    glDeleteRenderbuffers(1, &mRenderbufferId);
}

    
void Framebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferId);
}
    
void Framebuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
    
Color4f Framebuffer::ColorAtPoint(const Vec2& point)
{
    static const float d = 255.0f;
    unsigned char data[4] = {0};
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferId);
    glReadPixels (point.mX, point.mY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data);
    Color4f color;
    for (int i = 0; i < 4; ++i) {
        color[i] = data[i]/d;
    }
    return color;
}



}
