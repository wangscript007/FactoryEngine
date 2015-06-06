
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
    
    struct Face {
        std::string name;
        int mID;
        //glm::vec3 sceneCoords;
    };

    
    Query(ModelTree& modelTree);
    virtual ~Query() {}
    
    void Points(std::vector<Point*>& points) const;
    void Faces(std::vector<Face*>& faces) const;
    
private:
    ModelTree& mModelTree;
};
    
}

