
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

    Shader(const Data& data) { mData = data; }
    
    void Compile();
    
    const std::string& name() const { return mData.name; }
    const std::string& source() const { return mData.source; }
    GLuint identifier() const { return mId; }
    GLint status() const { return mStatus; }
    void setData(const Data& data) { mData = data; }
    
private:
    void CheckCompileStatus();
    
    Data mData;
    GLint mStatus;
    GLuint mId;
    
};

}

