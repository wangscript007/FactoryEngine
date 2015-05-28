
#pragma once

namespace ftr {

class ModelTree;

class Query
{
public:
    struct Point {
        std::string name;
        glm::vec3 sceneCoords;
    };
    
    Query(ModelTree& modelTree);
    virtual ~Query() {}
    
    void Points(std::vector<Point*>& points) const;
    
private:
    ModelTree& mModelTree;
};
    
}

