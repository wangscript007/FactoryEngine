
#include <ImportExport/ModelImporter.h>

#include <assimp/cimport.h>
#include <assimp/config.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>


namespace ftr {
    
void ModelImporter::Import(const std::string& path)
{
    unsigned aiPostProccesFlags = 0;
    aiPropertyStore* props = aiCreatePropertyStore();
    aiSetImportPropertyInteger(props, AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT );
    mScene = (aiScene*) aiImportFileExWithProperties(path.c_str(), aiPostProccesFlags, NULL, props);
    aiReleasePropertyStore(props);
    printf("num meshes %d", mScene->mNumMeshes);
}
    
    
}