

#include <Graph/Node.h>
#include <Processing/ColorPickingMapper.h>
#include <Processing/ModelTree.h>



namespace ftr {
    
const int kGamaSize = 255;
const int kGranularity = 1;
    
const int R_MASK = kGamaSize;
const int G_MASK = kGamaSize<<8; //65280
const int B_MASK = kGamaSize<<16; //16711680
    
#pragma mark - Class
    
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
    
#pragma mark - Instance
    
ColorPickingMapper::ColorPickingMapper(ModelTree& modelTree)
: mModelTree(&modelTree)
{
    
}


Node* ColorPickingMapper::NodeForColor(const glm::vec3& color)
{
    int pickingId = IntFromColor(color);
    if (Exist(pickingId)) {
        return mIntToNodeMap[pickingId];
    }
    return NULL;
}
    
Node* ColorPickingMapper::NodeForID(int nodeID)
{
    if (Exist(nodeID)) {
        return mIntToNodeMap[nodeID];
    }
    return NULL;
}
    
bool ColorPickingMapper::Exist(int pickingId)
{
    return mIntToNodeMap.find(pickingId) != mIntToNodeMap.end();
}
        
    
void ColorPickingMapper::MapPickingColors(enum Node::Type nodeType)
{
    
    switch (nodeType) {
        case Node::kPoint: break;
        case Node::kLine: break;
        case Node::kFace: MapPickingColorsForFaces(); break;
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
        int pickingId = (1+i)*kGranularity;
        mIntToNodeMap[pickingId] = groups[i];
        groups[i]->setPickingId(pickingId);
    }
}
    
void ColorPickingMapper::MapPickingColorsForFaces()
{
    mIntToNodeMap.clear();
    std::vector<GroupNode*>& groups = mModelTree->mGroups;
    int count = 0;
    for(auto &groupNode : groups) {
        for(auto &bodyNode : groupNode->mSubnodes) {
            for(int i = 0; i < bodyNode->mSubnodes.size(); ++i) {
                int pickingId = (1+count)*kGranularity;
                mIntToNodeMap[pickingId] = bodyNode->mSubnodes[i];
                bodyNode->mSubnodes[i]->setPickingId(pickingId);
                count++;
            }
        }
    }
}


    
    
}

