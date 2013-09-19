
#pragma once

#include <Shading/Shader.h>
#include <Shading/ShadersProgram.h>
#include <Shading/ShadersInput.h>

namespace ftr {
    
class ShadersLibrary
{
public:
    typedef std::map<std::string, ShadersProgram> ProgramsMap;
    
    virtual ~ShadersLibrary() {}
    void Add(const std::string& name, const std::string& source, GLenum type);
    void Add(Shader::Data& shaderData);
    
    void BuildProgramWithName(const std::string& name);
    void UseProgramWithName(const std::string& name);
    ShadersInput* InputForProgramWithName(const std::string& name);
    
private:
    ProgramsMap mProgramsMap;
};

}

