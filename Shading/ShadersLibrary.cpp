

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
    mSourceMap[shaderData.name] = shaderData;
}
    
    
}

