
#include <ImportExport/ModelImporter.h>
#include <Processing/ModelEditor.h>
#include <Graph/BodyNode.h>
#include <Utils/Description.h>

#include <assimp/cimport.h>
#include <assimp/config.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>


namespace ftr {
    
ModelImporter::ModelImporter(ModelEditor& modelEditor)
    :mModelEditor(modelEditor)
{
    
}
    
void ModelImporter::Import(const std::string& path)
{
    mModelEditor.CreateGroup();
    
    unsigned aiPostProccesFlags = aiProcess_OptimizeMeshes;
    aiPropertyStore* props = aiCreatePropertyStore();
    aiSetImportPropertyInteger(props, AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT );
    mScene = (aiScene*) aiImportFileExWithProperties(path.c_str(), aiPostProccesFlags, NULL, props);
    aiReleasePropertyStore(props);
    
    std::cout << "num meshes:" << mScene->mNumMeshes << std::endl;
    for (int i = 0; i < mScene->mNumMeshes; ++i) {
        mModelEditor.CreateBody();
        aiMesh* mesh = mScene->mMeshes[i];
        
        for (int l = 0; l < mesh->mNumVertices; ++l) {
            glm::vec3 vec(mesh->mVertices[l].x, mesh->mVertices[l].y, mesh->mVertices[l].z);
            printf("%s\n", Description::Described(vec).c_str());
            mModelEditor.CreatePoint(vec);
            
        }
        std::cout << "mesh " << i << ": " << mesh->mNumFaces << " faces" << std::endl;
        for (int j = 0; j < mesh->mNumFaces; ++j) {
            aiFace& face = mesh->mFaces[j];
            std::vector<PointNode*> nodes;
            for (int k = 0; k < face.mNumIndices; ++k) {
                unsigned int ind = face.mIndices[k];
                nodes.push_back(reinterpret_cast<PointNode*>(mModelEditor.activeBody()->mSubnodes[ind]));
            }
            mModelEditor.CreateFace(nodes);
        }
    }
}
    
}