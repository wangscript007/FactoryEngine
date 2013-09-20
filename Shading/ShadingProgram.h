
#pragma once

#include <Shading/Shader.h>

namespace ftr {

class ShadingInterface;
class ShadingProgram
{
public:
    enum Type {
        kMain,
        kColor,
        kTest,
        kCount
    };
    
    ShadingProgram();
    virtual ~ShadingProgram();
    
    void AddShader(const Shader& shader);
    void Link();
    void Activate();
    void CompileShaders();
    GLint status() const { return mStatus; }
    ShadingInterface* interface() const { return mInterface; }
    std::string mName;
    
private:
    typedef std::map<std::string, Type> NameToTypeMap;
    typedef std::vector<Shader> AttachedVector;
    void CheckLinkStatus();
    void DetachShaders();
    void AttachShaders();
    
    static Type TypeForName(const std::string& name);
    
    GLuint mId;
    GLint mStatus;
    
    AttachedVector attachedVector;
    ShadingInterface* mInterface;
};

}

