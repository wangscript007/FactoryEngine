
#include <Render/Framebuffer.h>

namespace ftr {

Framebuffer::Framebuffer(const Vec2& size)
{
    // create framebuffer
    glGenFramebuffers(1, &framebufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
    
    // attach renderbuffer to fb so that depth-sorting works
    glGenRenderbuffers(1, &renderbufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbufferId);
    glRenderbufferStorage(GL_RENDERBUFFER,
                          GL_DEPTH_COMPONENT,
                          size.mX,
                          size.mY);
    
    // create texture to use for rendering second pass
    glGenTextures (1, &framebufferTextureId);
    glBindTexture (GL_TEXTURE_2D, framebufferTextureId);
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
                              renderbufferId);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D,
                           framebufferTextureId,
                           0);
    // redirect fragment shader output 0 used to the texture that we just bound
    GLenum draw_bufs[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers (1, draw_bufs);
    
    Unbind();
}
    
Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &framebufferId);
    glDeleteTextures(1, &framebufferTextureId);
    glDeleteRenderbuffers(1, &renderbufferId);
}

    
void Framebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
}
    
void Framebuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


}
