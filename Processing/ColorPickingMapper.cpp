

#include <Graph/Node.h>
#include <Processing/ColorPickingMapper.h>
#include <Processing/ModelTree.h>



namespace ftr {
    
const int kGamaSize = 255;
    
const int R_MASK = kGamaSize;
const int G_MASK = kGamaSize<<8; //65280
const int B_MASK = kGamaSize<<16; //16711680
    
int ColorPickingMapper::IntFromColor(const glm::vec3& vec)
{
    int r = static_cast<int>(vec.x*kGamaSize);
    int g = static_cast<int>(vec.y*kGamaSize);
    int b = static_cast<int>(vec.z*kGamaSize);
    return r | (g << 8) | (b << 16);
}

glm::vec3 ColorPickingMapper::ColorFromInt(const int number)
{
    float r = (number & R_MASK)/255.0f;
    float g = ((number & G_MASK) >> 8)/255.0f;
    float b = ((number & B_MASK) >> 16)/255.0f;
    return glm::vec3(r, g, b);
}

        
ColorPickingMapper::ColorPickingMapper(ModelTree& modelTree)
    : mModelTree(&modelTree)
{
    
}
    
void ColorPickingMapper::MapPickingColors(enum Node::Type nodeType)
{
    
    switch (nodeType) {
        case Node::kPoint: break;
        case Node::kLine: break;
        case Node::kFace: break;
        case Node::kBody: break;
        case Node::kGroup: MapPickingColorsForGroups(); break;
            
        default:
            assert(false); // wrong type
            break;
    }
}
    
void ColorPickingMapper::MapPickingColorsForGroups()
{
    mIntToNodeMap.clear();
    std::vector<GroupNode*>& groups = mModelTree->mGroups;
    for(int i = 0; i < groups.size(); ++i) {
        mIntToNodeMap[i] = groups[i+1000];
        groups[i]->setPickingId(i+1000);
    }
}

    
    
}

