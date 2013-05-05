
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

