
#include <ImportExport/ModelImporter.h>
#include <Processing/ModelEditor.h>
#include <Graph/BodyNode.h>
#include <Utils/Description.h>
#include <Graph/PointNode.h>

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
    
    unsigned aiPostProccesFlags = aiProcess_RemoveComponent        |
    aiProcess_JoinIdenticalVertices       |
    aiProcess_OptimizeMeshes              |
    aiProcess_Triangulate              |
    aiProcess_OptimizeGraph;
    aiPropertyStore* props = aiCreatePropertyStore();
    aiSetImportPropertyInteger(props, AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT);
    aiSetImportPropertyInteger(props, AI_CONFIG_PP_RVC_FLAGS, aiComponent_CAMERAS       |
                               aiComponent_LIGHTS                                              |
                               aiComponent_MATERIALS                                      |
                               aiComponent_TEXTURES                                       |
                               aiComponent_BONEWEIGHTS                               |
                               aiComponent_COLORS                                            |
                               aiComponent_TANGENTS_AND_BITANGENTS |
                               aiComponent_NORMALS                                         |
                               aiComponent_ANIMATIONS);
    
    
    mScene = (aiScene*) aiImportFileExWithProperties(path.c_str(), aiPostProccesFlags, NULL, props);
    aiReleasePropertyStore(props);
    
    std::cout << "num meshes:" << mScene->mNumMeshes << std::endl;
    for (int i = 0; i < mScene->mNumMeshes; ++i) {
        mModelEditor.CreateBody();
        aiMesh* mesh = mScene->mMeshes[i];
        
        for (int l = 0; l < mesh->mNumVertices; ++l) {
            glm::vec3 vec(mesh->mVertices[l].x, mesh->mVertices[l].y, mesh->mVertices[l].z);
            //printf("%s\n", Description::Described(vec).c_str());
            mModelEditor.CreatePoint(vec);
            
        }
        std::cout << "mesh " << i << ": " << mesh->mNumFaces << " faces" << std::endl;
        std::vector<PointNode*> nodes;
        nodes.reserve(3);
        for (int j = 0; j < mesh->mNumFaces; ++j) {
            aiFace& face = mesh->mFaces[j];
            
            for (int k = 0; k < face.mNumIndices; ++k) {
                unsigned int ind = face.mIndices[k];
                nodes.push_back(reinterpret_cast<PointNode*>(mModelEditor.activeBody()->mSubnodes[ind]));
            }
            // faces with lines
            for (int k = 0; k < nodes.size()-1; k++ ) {
                if (!nodes[k]->IsConnectedTo(*nodes[k+1])) {
                    mModelEditor.CreateLine(nodes[k], nodes[k+1]);
                }
            }
            
            // faces without line
            //mModelEditor.CreateFace(nodes);
            nodes.clear();
        }
    }
}
    
}