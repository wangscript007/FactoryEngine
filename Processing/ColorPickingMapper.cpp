

#include <Graph/Node.h>
#include <Processing/ColorPickingMapper.h>
#include <Processing/ModelTree.h>



namespace ftr {
    
const int B_MASK = 255;
const int G_MASK = 255<<8; //65280
const int R_MASK = 255<<16; //16711680
    
int ColorPickingMapper::IntFromColor(glm::vec3& vec)
{
    int r = vec.x;
    int g = vec.y;
    int b = vec.z;
    return r | (g << 8) | (b << 16);
}

glm::vec4 ColorPickingMapper::ColorFromInt(int number)
{
    int r = number & R_MASK;
    int g = number & G_MASK;
    int b = number & B_MASK;
    return glm::vec4(r, g, b, 1.0f);
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
        mIntToNodeMap[i] = groups[i];
        groups[i]->setPickingId(i);
    }
}

    
    
}

