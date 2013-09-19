
#include <Shading/ShadersProgram.h>
    
namespace ftr {
    
ShadersProgram::ShadersProgram()
{
    mId = glCreateProgram();
    mShadersInput = new ShadersInput(mId);
    assert(mId != 0);
}
    
ShadersProgram:: ~ShadersProgram()
{
//    glDeleteProgram(mId);
    FT_DELETE(mShadersInput);
}
    
void ShadersProgram::Activate()
{
    glUseProgram(mId);
}
void ShadersProgram::Deactivate()
{
    glUseProgram(0);
}
    
void ShadersProgram::AddShader(const Shader& shader)
{
    assert(shader.identifier() > 0);
    assert(mId > 0);
    attachedVector.push_back(shader);
}
    
void ShadersProgram::CompileShaders()
{
    for (auto it = attachedVector.begin(); it != attachedVector.end(); ++it) {
        Shader& shader = *it;
        shader.Compile();
    }
}
    
void ShadersProgram::Link()
{
    for (auto it = attachedVector.begin(); it != attachedVector.end(); ++it) {
        Shader& shader = *it;
        glAttachShader(mId, shader.identifier());
    }
    assert(attachedVector.size() > 0);
    mShadersInput->BindOutput();
    glLinkProgram(mId);
    CheckLinkStatus();
    DetachShaders();
    mShadersInput->Init();
}
    

    
void ShadersProgram::CheckLinkStatus()
{
    glGetProgramiv(mId, GL_LINK_STATUS, &mStatus);
    
    if (mStatus == GL_FALSE) {
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
        glDetachShader(mId, attachedVector[i].identifier());
    }
    attachedVector.clear();
}
        
}

