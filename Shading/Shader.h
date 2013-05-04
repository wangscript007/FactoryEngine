
#pragma once

#include <Shading/Shader.h>

namespace ftr {

class Shader
{
public:
    struct Data {
        std::string name;
        std::string source;
        GLenum type;
    };

    Shader(const Data& data);
    virtual ~Shader() {}
    
    void Compile();
    
    const std::string& name() const { return mName; }
    const std::string& source() const { return mSource; }
    GLuint identifier() const { return mId; }
    GLint status() const { return mStatus; }
    
private:
    void CheckCompileStatus();
    
    std::string mName;
    std::string mSource;
    GLenum mType;
    
    GLint mStatus;
    GLuint mId;
    
};

}

