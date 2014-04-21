

#pragma once

#include <Graph/Node.h>
#include <Graph/GroupNode.h>

namespace ftr {
    
class ColorPickingMapper
{
public:
    ColorPickingMapper() {};
    ~ColorPickingMapper() {};
//    void MapLevel(GroupNode::Level level);
    
    
private:
    static int IntFromColor(glm::vec3& vec);
    static glm::vec3 ColorFromInt(int number);
    
    std::map<int, Node*> mIntToNodeMap;
    GroupNode* mRootNode;
};
    
}

