
#pragma once

namespace ftr {

class PolygonBatch
{
public:
    struct Data {
        std::vector<glm::vec4> vertices;
        std::vector<glm::vec4> normals;
        std::vector<glm::vec4> colors;
        std::vector<glm::vec4> pickingColors;
    };
    virtual ~PolygonBatch() {}
    
    
private:
    void ClearRenderData();
    char* CreateRenderData(ShadingInterface& shadingInterface);
};

}

