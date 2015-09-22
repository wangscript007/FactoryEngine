
#pragma once

#include <Render/Primitive.h>
#include "FTTypes.h"

namespace ftr {
    
class Batch : public Primitive
{
public:
    Batch();
    virtual ~Batch();
    virtual void AddPrimitive(Primitive& primitive);
    virtual void CreateRenderData(ShadingInterface& shadingInterface) {}
    
    FTUnsigned size() const { return  static_cast<FTUnsigned>(mPrimitives.size()); }
    FTUnsigned vertexArrayObjectId() const { return mVertexArrayObjectId; }
    std::string Description() const;
    bool IsZombie() { return mRenderData && mIsInvalid; }
    bool AcceptsPrimitives() { return mIsInvalid && !IsZombie(); };
    
protected:
    void ClearRenderData();
    
    std::vector<Primitive*> mPrimitives;
    
    FTUnsigned mVertexArrayObjectId;
    FTUnsigned mBuffers[4];
    FTUnsigned mBuffersCount;
    char* mRenderData;
};
    
}

