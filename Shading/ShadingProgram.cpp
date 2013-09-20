
#include <Shading/ShadingProgram.h>
    
namespace ftr {
    
ShadingProgram::ShadingProgram()
{
    mId = glCreateProgram();
    mShadingInterface = new ShadingInterface(mId);
    assert(mId != 0);
}
    
ShadingProgram:: ~ShadingProgram()
{
//    glDeleteProgram(mId);
    FT_DELETE(mShadingInterface);
}
    
void ShadingProgram::Activate()
{
    glUseProgram(mId);
}
void ShadingProgram::Deactivate()
{
    glUseProgram(0);
}
    
void ShadingProgram::AddShader(const Shader& shader)
{
    assert(shader.identifier() > 0);
    assert(mId > 0);
    attachedVector.push_back(shader);
}
    
void ShadingProgram::CompileShaders()
{
    for (auto it = attachedVector.begin(); it != attachedVector.end(); ++it) {
        Shader& shader = *it;
        shader.Compile();
    }
}
    
void ShadingProgram::Link()
{
    AttachShaders();
    assert(attachedVector.size() > 0);
    mShadingInterface->BindOutput();
    glLinkProgram(mId);
    CheckLinkStatus();
    DetachShaders();
    mShadingInterface->SetupForProgramWithName(mName);
}
    

    
void ShadingProgram::CheckLinkStatus()
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
    
void ShadingProgram::AttachShaders()
{
    for (auto it = attachedVector.begin(); it != attachedVector.end(); ++it) {
        Shader& shader = *it;
        glAttachShader(mId, shader.identifier());
    }
}

    
void ShadingProgram::DetachShaders()
{
    for(int i = 0; i < attachedVector.size(); ++i) {
        glDetachShader(mId, attachedVector[i].identifier());
    }
    attachedVector.clear();
}
        
}

