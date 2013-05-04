
#pragma once

#include <Shading/ShadersLibrary.h>
#include <Shading/ShaderFactory.h>
#include <Shading/ShadersProgram.h>

namespace ftr {

class ShadersManager
{
public:
    typedef std::map<std::string, Shader*> ShadersMap;
    
    virtual ~ShadersManager() {}
    
    void LinkProgram();
    
private:
    void Compile(const Shader& shader);
    
    ShadersMap mMap;
    ShadersProgram mProgram;
    ShadersLibrary mLibrary;
    
};

}

