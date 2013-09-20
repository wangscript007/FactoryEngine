
#pragma once

#include <Shading/Shader.h>
#include <Shading/ShadersInput.h>

namespace ftr {

class ShadersProgram
{
public:
    ShadersProgram();
    virtual ~ShadersProgram();
    
    void AddShader(const Shader& shader);
    void Link();
    void Activate();
    void Deactivate();
    void CompileShaders();
    GLint status() const { return mStatus; }
    ShadersInput* shaderInput() const { return mShadersInput; }
    std::string mName;
private:
    typedef std::vector<Shader> AttachedVector;
    void CheckLinkStatus();
    void DetachShaders();
    void AttachShaders();
    
    GLuint mId;
    GLint mStatus;

    
    AttachedVector attachedVector;
    ShadersInput* mShadersInput;
};

}

