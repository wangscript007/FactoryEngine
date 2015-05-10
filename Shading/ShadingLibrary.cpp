

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
    ShadingProgram::Type programType = ShadingProgram::TypeForName(shaderData.name);
    ShadingProgram& program = mProgramsMap[programType];
    program.AddShader(Shader(shaderData));
}
    
    
void ShadingLibrary::clear()
{
    mProgramsMap.clear();
}
    
    
void ShadingLibrary::BuildProgramWithType(ShadingProgram::Type type)
{
    ShadingProgram& program = mProgramsMap[type];
    program.mType = type;
    program.CompileShaders();
    mInterface.BindOutput(program.indentifier());
    program.Link();
    mInterface.CreateInterfaceForProgram(program.mType, program.indentifier());
}
    
    
void ShadingLibrary::UseProgramWithType(ShadingProgram::Type type)
{
    if (type == ShadingProgram::kNone) {
        glUseProgram(0);
    } else {
        mProgramsMap[type].Activate();
        mInterface.ActvateBondForProgramType(type);

    }
}
    
}
