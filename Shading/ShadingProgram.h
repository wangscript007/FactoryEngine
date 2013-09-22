
#pragma once

#include <Shading/Shader.h>

namespace ftr {

class ShadingInterface;
class ShadingProgram
{
public:
    enum Type {
        kNone,
        kMain,
        kColor,
        kTest,
        kCount
    };

    static Type TypeForName(const std::string& name);
    
    ShadingProgram();
    virtual ~ShadingProgram();
    
    void AddShader(const Shader& shader);
    void Link();
    void Activate();
    void CompileShaders();
    GLint status() const { return mStatus; }
    GLint indentifier() const { return mId; }
    Type mType;
    
private:
    typedef std::map<std::string, Type> NameToTypeMap;
    typedef std::vector<Shader> AttachedVector;
    void CheckLinkStatus();
    void DetachShaders();
    void AttachShaders();
    
    GLuint mId;
    GLint mStatus;
    
    AttachedVector attachedVector;
    ShadingInterface* mInterface;
    
    
};

}

