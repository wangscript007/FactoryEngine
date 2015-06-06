

#pragma once

#include <Graph/Node.h>
#include <Graph/GroupNode.h>

namespace ftr {
    
class ModelTree;
    
class ColorPickingMapper
{
public:
    static int IntFromColor(const glm::vec3& vec);
    static glm::vec3 ColorFromInt(const int number);
    
    ColorPickingMapper(ModelTree& modelTree);
    ~ColorPickingMapper() {};
    
    void MapPickingColors(enum Node::Type nodeType);
    Node* NodeForColor(const glm::vec3& color);
    Node* NodeForID(int nodeID);
    
    
    
private:
    
    void MapPickingColorsForGroups();
    void MapPickingColorsForFaces();
    
    bool Exist(int pickingId);
    
    std::map<int, Node*> mIntToNodeMap;
    
    ModelTree* mModelTree;
};
    
}

