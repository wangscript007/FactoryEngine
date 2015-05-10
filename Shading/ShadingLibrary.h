
#pragma once

#include <Shading/Shader.h>
#include <Shading/ShadingProgram.h>
#include <Shading/ShadingInterface.h>

namespace ftr {
    
    
class ShadingLibrary
{
public:
    typedef std::map<ShadingProgram::Type, ShadingProgram> ProgramsMap;
    
    virtual ~ShadingLibrary() {}
    void Add(const std::string& name, const std::string& source, GLenum type);
    void Add(Shader::Data& shaderData);
    
    void clear();
    
    void BuildProgramWithType(ShadingProgram::Type type);
    void UseProgramWithType(ShadingProgram::Type type);
    
    ShadingInterface& interface() { return mInterface; }
private:
    ProgramsMap mProgramsMap;
    ShadingInterface mInterface;
};

}

