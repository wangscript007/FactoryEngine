
#include <Render/Batch.h>

namespace ftr {
    
Batch::Batch() :
    mRenderData(NULL),
    mBuffersCount(0),
    mVertexArrayObjectId(0),
    mChanges(kChangeNone),
    mAcceptsValidPrimitives(true),
    mPrimitivesClearPending(false),
    mPrimitivesClearAllowed(false)
{
    
}
    
Batch::~Batch()
{
    ClearRenderData();
}
    
void Batch::ClearRenderData()
{
    if (mRenderData) {
        delete[] mRenderData;
        mRenderData = NULL;
        glDeleteBuffers(mBuffersCount, mBuffers);
        glDeleteVertexArrays(1, &mVertexArrayObjectId);
    }
}
    
void Batch::UpdateRenderData(ShadingInterface& shadingInterface)
{
    ClearPrimitives();
    
    if (mIsInvalid) {
        ClearRenderData();
        CreateRenderData(shadingInterface);
        mIsInvalid = false;
        mChanges = kChangeNone;
        mAcceptsValidPrimitives = false;
    }
    
    mPrimitivesClearAllowed = true;
}

    
void Batch::AddPrimitive(Primitive& primitive)
{
    ClearPrimitives();
    
    if (mAcceptsValidPrimitives || primitive.isInvalid()) {
        if (size() == 0) {
            mOptions = primitive.mOptions;
        }
        primitive.mBatch = this;
        primitive.Validate();
        mPrimitives.push_back(&primitive);
        mIsInvalid = true;
    }
}
    
void Batch::ClearPrimitives()
{
    if (mPrimitivesClearAllowed && mPrimitivesClearPending) {
        mPrimitives.clear();
        mPrimitivesClearPending = false;
        mAcceptsValidPrimitives = true;
    }
}
    
    
void Batch::Invalidate()
{
    if (mIsInvalid) return;
    
    mPrimitivesClearPending = true;
    // Primitive can be invalidate in the middle of render
    // so allowing to clear only after data update
    mPrimitivesClearAllowed = false;
    
    Primitive::Invalidate();
}

    
}

