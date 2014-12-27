
#pragma once



namespace ftr {
    
class ShadingInterface;
class PolygonPrimitive;

class PolygonBatch
{
public:
    PolygonBatch();
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
    void Triangulate();
    void AppendRenderData(const PolygonPrimitive& primitive);
    
    std::vector<PolygonPrimitive*> mPolygons;
    Data mRenderData;
    int mSize;
};
    
    
}