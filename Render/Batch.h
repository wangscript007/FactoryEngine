
#pragma once

#include <Render/Primitive.h>

namespace ftr {
    
extern const int kBatchSizeLimit;
    
class BatchBucket;

class Batch : public Primitive
{
public:
    Batch();
    virtual ~Batch();
    virtual void AddPrimitive(Primitive& primitive);
    virtual void Invalidate();
    
    void UpdateRenderData(ShadingInterface& shadingInterface);
    GLuint size() const { return  static_cast<GLuint>(mPrimitives.size()); }
    GLuint vertexArrayObjectId() const { return mVertexArrayObjectId; }
    
    bool IsFull() const { return option(kBatchFull); }
    BatchBucket* mBatchBucket;
    
protected:
    void ClearRenderData();
    void ClearPrimitives();
    
    void setFull(bool full) { setOption(kBatchFull, full); }
    
    virtual void CreateRenderData(ShadingInterface& shadingInterface) {}
    
    std::vector<Primitive*> mPrimitives;
    
    GLuint mVertexArrayObjectId;
    GLuint mBuffers[4];
    GLuint mBuffersCount;
    char* mRenderData;

    bool mAcceptsValidPrimitives;
    bool mPrimitivesClearPending;
    bool mPrimitivesClearAllowed;
};
    
}

