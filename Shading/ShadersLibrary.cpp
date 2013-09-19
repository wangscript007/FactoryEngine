

#include <Shading/ShadersLibrary.h>

namespace ftr {
    
void ShadersLibrary::Add(const std::string& name, const std::string& source, GLenum type)
{
    Shader::Data data;
    data.name = name;
    data.source = source;
    data.type = type;
    Add(data);
}
    
void ShadersLibrary::Add(Shader::Data& shaderData)
{
    ShadersProgram& program = mProgramsMap[shaderData.name];
    program.AddShader(Shader(shaderData));
}
    
    
void ShadersLibrary::BuildProgramWithName(const std::string& name)
{
    ShadersProgram& program = mProgramsMap[name];
    program.CompileShaders();
    program.Link();
 
}
    
void ShadersLibrary::UseProgramWithName(const std::string& name)
{
    if (name == "none") {
        glUseProgram(0);
    } else {
        mProgramsMap[name].Activate();
    }
}
    
ShadersInput* ShadersLibrary::InputForProgramWithName(const std::string& name)
{
    return mProgramsMap[name].shaderInput();
}
    
}
