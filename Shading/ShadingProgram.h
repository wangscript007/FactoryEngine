
#pragma once

#include <Shading/Shader.h>
#include <Shading/ShadingInterface.h>

namespace ftr {

class ShadingProgram
{
public:
    ShadingProgram();
    virtual ~ShadingProgram();
    
    void AddShader(const Shader& shader);
    void Link();
    void Activate();
    void Deactivate();
    void CompileShaders();
    GLint status() const { return mStatus; }
    ShadingInterface* shaderInput() const { return mShadingInterface; }
    std::string mName;
private:
    typedef std::vector<Shader> AttachedVector;
    void CheckLinkStatus();
    void DetachShaders();
    void AttachShaders();
    
    GLuint mId;
    GLint mStatus;

    
    AttachedVector attachedVector;
    ShadingInterface* mShadingInterface;
};

}

