
#pragma once

#include <Render/Primitive.h>

namespace ftr {
    
class Batch : public Primitive
{
public:
    Batch();
    virtual ~Batch();
    virtual void AddPrimitive(Primitive& primitive);
    virtual void CreateRenderData(ShadingInterface& shadingInterface) {}
    
    GLuint size() const { return  static_cast<GLuint>(mPrimitives.size()); }
    GLuint vertexArrayObjectId() const { return mVertexArrayObjectId; }
    std::string Description() const;
    bool IsZombie() { return mRenderData && mIsInvalid; }
    bool AcceptsPrimitives() { return mIsInvalid && !IsZombie(); };
    
protected:
    void ClearRenderData();
    
    std::vector<Primitive*> mPrimitives;
    
    GLuint mVertexArrayObjectId;
    GLuint mBuffers[4];
    GLuint mBuffersCount;
    char* mRenderData;
};
    
}

