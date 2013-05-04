
#include <Shading/ShadersProgram.h>
    
namespace ftr {
    
ShadersProgram::ShadersProgram()
{
    mId = glCreateProgram();
}
    
void ShadersProgram::AttachShader(const Shader& shader)
{
    glAttachShader(mId, shader.identifier());
    attachedVector.push_back(shader.identifier());
}
    
void ShadersProgram::Link()
{
    glLinkProgram(mId);
    CheckLinkStatus();
    DetachShaders();
}
    
void ShadersProgram::CheckLinkStatus()
{
    glGetProgramiv(mId, GL_LINK_STATUS, &mStatus);
    if (mStatus == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(mId, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
}
    
void ShadersProgram::DetachShaders()
{
    for(int i = 0; i < attachedVector.size(); ++i) {
        glDetachShader(mId, attachedVector[i]);
    }
    attachedVector.clear();
}
    
}

