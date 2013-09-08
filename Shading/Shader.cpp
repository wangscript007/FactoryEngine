
#include <Shading/Shader.h>

namespace ftr {

Shader::Shader(const Data& data)
:mName(data.name), mSource(data.source), mType(data.type)
{
    assert((mType == GL_FRAGMENT_SHADER) || (mType == GL_VERTEX_SHADER));
}
    
Shader::~Shader()
{
//    glDeleteShader(mId);
}
    
void Shader::Compile()
{
    mId = glCreateShader(mType);
    assert(mId != 0);
    const char* source = mSource.c_str();
    glShaderSource(mId, 1, &source, NULL);
    glCompileShader(mId);
    CheckCompileStatus();
}
    
void Shader::CheckCompileStatus()
{
    glGetShaderiv(mId, GL_COMPILE_STATUS, &mStatus);
    if (mStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(mId, infoLogLength, NULL, strInfoLog);
        
        const char *strShaderType = NULL;
        switch(mType)
        {
            case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
            case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }
        
        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;
        
        assert(false);
    }
    
    
}
    
}

