
#pragma once

#include <Render/Primitive.h>

namespace ftr {

class Batch : public Primitive
{
public:
    enum Change {
        kChangeNone                = 0,
        kChangeNewPrimitive        = 1 << 1,
        kChangeRemovedPrimitive    = 1 << 2
    };
    
    Batch();
    virtual ~Batch();
    virtual void AddPrimitive(Primitive& primitive);
    virtual void Invalidate();
    
    void AddChange(Change change) { mChanges |= static_cast<unsigned int>(change); }
    bool ContainsChange(Change change) { return (mChanges & static_cast<unsigned int>(change)) != 0; }
    
    void UpdateRenderData(ShadingInterface& shadingInterface);
    GLuint size() const { return  static_cast<GLuint>(mPrimitives.size()); }
    GLuint vertexArrayObjectId() const { return mVertexArrayObjectId; }
    
protected:
    std::vector<Primitive*> mPrimitives;
    void ClearRenderData();
    virtual void CreateRenderData(ShadingInterface& shadingInterface) {}
    GLuint mVertexArrayObjectId;
    GLuint mBuffers[4];
    GLuint mBuffersCount;
    char* mRenderData;

    bool mAcceptsNewPrimitives;
    
    bool mClearPrimitives;
    bool mUpdatePassed;
    
    unsigned int mChanges;

};
    
}

