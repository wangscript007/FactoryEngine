
#include <Shading/ShadingProgram.h>
#include <Shading/ShadingInterface.h>
    
namespace ftr {
    
    
ShadingProgram::ShadingProgram()
{
    mId = glCreateProgram();
    assert(mId != 0);
}
    
ShadingProgram:: ~ShadingProgram()
{
//    glDeleteProgram(mId);
    FT_DELETE(mInterface);
}
    
void ShadingProgram::Activate()
{
    glUseProgram(mId);
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
    glLinkProgram(mId);
    CheckLinkStatus();
    DetachShaders();
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
    
ShadingProgram::Type ShadingProgram::TypeForName(const std::string& name)
{
    static NameToTypeMap map;
    if (!map.size()) {
        map.insert(std::make_pair("main",   kMain));
        map.insert(std::make_pair("color",  kColor));
        map.insert(std::make_pair("test",   kTest));
        assert(map.size() == kCount - 1);
    }
    return map[name];
    
}
        
}

