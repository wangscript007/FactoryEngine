
#pragma once

#include <Render/Primitive.h>

namespace ftr {
    
class ShadingInterface;

class PolygonBatch : public Primitive
{
public:
    Type type() const { return kPolygon; }
    
    PolygonBatch();
    virtual ~PolygonBatch() {}

    int size() const { return mSize; }
    int triangesCount() const { return mTrianglesCount; }
    
    void Invalidate();
    void AddPolygon(Primitive& primitive);
    void Clear();
    
private:
    void CreateRenderData(ShadingInterface& shadingInterface);
    std::vector<PolygonPrimitive*> mPolygons;
    int mSize;
    int mTrianglesCount;
};
    
}