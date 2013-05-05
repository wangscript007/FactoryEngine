
#include <Shading/ShadersManager.h>

namespace ftr {
    
ShadersManager::~ShadersManager()
{
    Clear();
}
    
void ShadersManager::Clear()
{
    for (auto it = mShadersMap.begin(); it != mShadersMap.end(); ++it) {
        Shader* shader = (*it).second;
        FT_DELETE(shader);
    }
    mShadersMap.clear();
}
    
void ShadersManager::CreateShadersFromLibrary(const ShadersLibrary& library)
{
    ShadersLibrary::SourceMap sourceMap = library.sourceMap();
    for (auto it = sourceMap.begin(); it != sourceMap.end(); ++it) {
        const Shader::Data data = (*it).second;
        Shader* shader = new Shader(data);
        mShadersMap[data.name] = shader;
    }
}
    
void ShadersManager::CompileShaders()
{
    for (auto it = mShadersMap.begin(); it != mShadersMap.end(); ++it) {
        Shader* shader = (*it).second;
        shader->Compile();
    }
}
    
void ShadersManager::LinkProgram()
{
    for (auto it = mShadersMap.begin(); it != mShadersMap.end(); ++it) {
        Shader* shader = (*it).second;
        mShadersProgram.AttachShader(*shader);
    }
    mShadersProgram.Link();
}

}