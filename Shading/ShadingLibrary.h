
#pragma once

#include <Shading/Shader.h>
#include <Shading/ShadingProgram.h>
#include <Shading/ShadingInterface.h>

namespace ftr {
    
    
class ShadingLibrary
{
public:
    typedef std::map<std::string, ShadingProgram> ProgramsMap;
    
    virtual ~ShadingLibrary() {}
    void Add(const std::string& name, const std::string& source, GLenum type);
    void Add(Shader::Data& shaderData);
    
    void BuildProgramWithName(const std::string& name);
    void UseProgramWithName(const std::string& name);
    ShadingInterface* InputForProgramWithName(const std::string& name);
    
private:
    ProgramsMap mProgramsMap;
};

}

