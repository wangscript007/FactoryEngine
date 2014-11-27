
#include <assimp/scene.h>

namespace ftr {
    
class ModelEditor;
    
class ModelImporter
{
public:
    ModelImporter(ModelEditor& modelEditor);
    void Import(const std::string& path);
    
private:
    aiScene* mScene;
    ModelEditor& mModelEditor;
};

    
    
}

