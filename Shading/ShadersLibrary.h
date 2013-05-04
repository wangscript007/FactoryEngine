
#pragma once

#include <Shading/Shader.h>

namespace ftr {
    
class ShadersLibrary
{
public:
    typedef std::map<std::string, Shader::Data> SourceMap;
    
    void Load();
    void Add(Shader::Data& shaderData);
    virtual ~ShadersLibrary() {}
    const SourceMap& sourceMap() const { return mSourceMap; }
    
private:
    SourceMap mSourceMap;
};

}

