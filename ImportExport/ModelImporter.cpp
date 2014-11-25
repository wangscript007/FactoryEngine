
#include <ImportExport/ModelImporter.h>

#include <assimp/cimport.h>
#include <assimp/config.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>


namespace ftr {
    
void ModelImporter::Import(const std::string& path)
{
    unsigned aiPostProccesFlags = aiProcess_OptimizeMeshes;
    aiPropertyStore* props = aiCreatePropertyStore();
    aiSetImportPropertyInteger(props, AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT );
    mScene = (aiScene*) aiImportFileExWithProperties(path.c_str(), aiPostProccesFlags, NULL, props);
    aiReleasePropertyStore(props);
    std::cout << "num meshes:" << mScene->mNumMeshes << std::endl;
    for (int i = 0; i < mScene->mNumMeshes; ++i) {
        aiMesh* mesh = mScene->mMeshes[i];
        std::cout << "mesh " << i << ": " << mesh->mNumFaces << " faces" << std::endl;
        for (int j = 0; j < mesh->mNumFaces; ++j) {
            aiFace& face = mesh->mFaces[j];
            std::cout << face.mNumIndices << std::endl;
            for (int k = 0; k < face.mNumIndices; ++k) {
                
                std::cout << "x: " << mesh->mVertices[k].x << ", y: " << mesh->mVertices[k].y << ", z: " << mesh->mVertices[k].z << std::endl;
                ;
            }
        }
    }
}
}