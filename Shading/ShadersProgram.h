
#pragma once

#include <Shading/Shader.h>

namespace ftr {

class ShadersProgram
{
public:
    ShadersProgram();
    virtual ~ShadersProgram() {}
    
    void AttachShader(const Shader& shader);
    void Link();
    void Activate();
    void Deactivate();
    GLuint AttributeLocation(const std::string& name) { return glGetAttribLocation(mId, name.c_str()); }
    GLuint UniformLocation(const std::string& name) { return glGetUniformLocation(mId, name.c_str()); }
    GLint status() const { return mStatus; }
    
    
private:
    typedef std::vector<GLuint> AttachedVector;
    void CheckLinkStatus();
    void DetachShaders();
    
    GLuint mId;
    GLint mStatus;
    AttachedVector attachedVector;
};

}

