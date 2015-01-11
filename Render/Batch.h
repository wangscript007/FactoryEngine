
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
    GLuint size() const { return  static_cast<GLuint>(mPrimitives.size()); }
    GLuint vertexArrayObjectId() const { return mVertexArrayObjectId; }
    
    bool ClearPrimitives();
    bool mPrimitivesClearPending;
    
protected:
    void ClearRenderData();
    
    virtual void CreateRenderData(ShadingInterface& shadingInterface) {}
    
    std::vector<Primitive*> mPrimitives;
    
    GLuint mVertexArrayObjectId;
    GLuint mBuffers[4];
    GLuint mBuffersCount;
    char* mRenderData;

    bool mAcceptsValidPrimitives;
    bool mPrimitivesClearAllowed;
};
    
}

