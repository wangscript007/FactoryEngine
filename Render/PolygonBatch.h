
#pragma once

#include <Render/Batch.h>

namespace ftr {
    
class ShadingInterface;

class PolygonBatch : public Batch
{
public:
    Type type() const { return kPolygon; }
    PolygonBatch();
    virtual ~PolygonBatch() {}
    virtual void CreateRenderData(ShadingInterface& shadingInterface);
    
    int trianglesCount() const { return mTrianglesCount; }
    
private:
    int mTrianglesCount;
};
    
}