

#pragma once

#include <Graph/Node.h>
#include <Graph/GroupNode.h>

namespace ftr {
    
class ModelTree;
    
class ColorPickingMapper
{
public:
    static int IntFromColor(glm::vec3& vec);
    static glm::vec4 ColorFromInt(int number);
    
    ColorPickingMapper(ModelTree& modelTree);
    ~ColorPickingMapper() {};
    
    void MapPickingColors(enum Node::Type nodeType);
    
    
private:
    
    void MapPickingColorsForGroups();
    
    std::map<int, Node*> mIntToNodeMap;
    
    ModelTree* mModelTree;
};
    
}

