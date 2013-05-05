
#include <Shading/ShadersProgram.h>
    
namespace ftr {
    
ShadersProgram::ShadersProgram()
{
    mId = glCreateProgram();
    assert(mId != 0);
}
    
void ShadersProgram::Activate()
{
    glUseProgram(mId);
}
void ShadersProgram::Deactivate()
{
    glUseProgram(0);
}
    
void ShadersProgram::AttachShader(const Shader& shader)
{
    assert(shader.identifier() > 0);
    assert(mId > 0);
    glAttachShader(mId, shader.identifier());
    attachedVector.push_back(shader.identifier());
}
    
void ShadersProgram::Link()
{
    assert(attachedVector.size() > 0);
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
        assert(false);
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

