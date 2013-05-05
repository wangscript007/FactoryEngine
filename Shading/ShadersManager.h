
#pragma once

#include <Shading/ShadersLibrary.h>
#include <Shading/ShadersProgram.h>

namespace ftr {

class ShadersManager
{
public:
    typedef std::map<std::string, Shader*> ShadersMap;
    ShadersManager();
    virtual ~ShadersManager();
    void CreateShadersFromLibrary(const ShadersLibrary& library);
    void CompileShaders();
    void LinkProgram();
    void Clear();
    
    ShadersProgram* shadersProgram() { return mShadersProgram; }
    
private:
    ShadersMap mShadersMap;
    ShadersProgram* mShadersProgram;
};

}

