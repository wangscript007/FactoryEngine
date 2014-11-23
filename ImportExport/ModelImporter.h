
#include <assimp/scene.h>

namespace ftr {
    

    
class ModelImporter
{
    
public:
    void Import(const std::string& path);
private:
    aiScene* mScene;
};

    
    
}

