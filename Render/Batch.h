
#pragma once

#include <Render/Primitive.h>

namespace ftr {

class Batch : public Primitive
{
public:
    Batch();
    virtual ~Batch();
    virtual void AddPrimitive(Primitive& primitive);
    virtual void Invalidate();
    
    void UpdateRenderData(ShadingInterface& shadingInterface);
    size_t size() const { return mPrimitives.size(); }
    GLuint vertexArrayObjectId() const { return mVertexArrayObjectId; }
    
protected:
    std::vector<Primitive*> mPrimitives;
    void ClearRenderData();
    virtual void CreateRenderData(ShadingInterface& shadingInterface) {}
    GLuint mVertexArrayObjectId;
    GLuint mBuffers[4];
    GLuint mBuffersCount;
    char* mRenderData;

};
    
}

