

#include <Shading/ShadingLibrary.h>

namespace ftr {
    
void ShadingLibrary::Add(const std::string& name, const std::string& source, GLenum type)
{
    Shader::Data data;
    data.name = name;
    data.source = source;
    data.type = type;
    Add(data);
}
    
void ShadingLibrary::Add(Shader::Data& shaderData)
{
    ShadingProgram& program = mProgramsMap[shaderData.name];
    program.AddShader(Shader(shaderData));
}
    
    
void ShadingLibrary::BuildProgramWithName(const std::string& name)
{
    ShadingProgram& program = mProgramsMap[name];
    program.CompileShaders();
    program.mName = name;
    program.Link();
 
}
    
void ShadingLibrary::UseProgramWithName(const std::string& name)
{
    if (name == "none") {
        glUseProgram(0);
    } else {
        mProgramsMap[name].Activate();
    }
}
    
ShadingInterface* ShadingLibrary::InputForProgramWithName(const std::string& name)
{
    return mProgramsMap[name].shaderInput();
}
    
}
