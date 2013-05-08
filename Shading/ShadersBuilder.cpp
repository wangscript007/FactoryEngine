
#include <Shading/ShadersBuilder.h>

namespace ftr {
    
ShadersBuilder::ShadersBuilder()
    :mShadersProgram(NULL)
{
    
}
    
ShadersBuilder::~ShadersBuilder()
{
    Clear();
}
    
void ShadersBuilder::Clear()
{
    for (auto it = mShadersMap.begin(); it != mShadersMap.end(); ++it) {
        Shader* shader = (*it).second;
        FT_DELETE(shader);
    }
    mShadersMap.clear();
    FT_DELETE(mShadersProgram);
}
    
void ShadersBuilder::CreateShadersFromLibrary(const ShadersLibrary& library)
{
    ShadersLibrary::SourceMap sourceMap = library.sourceMap();
    for (auto it = sourceMap.begin(); it != sourceMap.end(); ++it) {
        const Shader::Data data = (*it).second;
        Shader* shader = new Shader(data);
        mShadersMap[data.name] = shader;
    }
}
    
void ShadersBuilder::CompileShaders()
{
    for (auto it = mShadersMap.begin(); it != mShadersMap.end(); ++it) {
        Shader* shader = (*it).second;
        shader->Compile();
    }
}
    
void ShadersBuilder::LinkProgram()
{
    if (mShadersProgram) {
        FT_DELETE(mShadersProgram);
        assert(false);
    }
    mShadersProgram = new ShadersProgram();
    for (auto it = mShadersMap.begin(); it != mShadersMap.end(); ++it) {
        Shader* shader = (*it).second;
        mShadersProgram->AttachShader(*shader);
    }
    mShadersProgram->Link();
}

}