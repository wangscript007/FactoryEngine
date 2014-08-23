
#include <Shading/Shader.h>

namespace ftr {
    
    
void Shader::Compile()
{
    printf("GLSL Version = %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("GL Version = %s\n", glGetString(GL_VERSION));
    mId = glCreateShader(mData.type);
    assert(mId != 0);
    const char* source = mData.source.c_str();
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
        switch(mData.type)
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

