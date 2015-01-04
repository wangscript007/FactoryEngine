
#include <Render/Batch.h>

namespace ftr {
    
Batch::Batch() :
    mRenderData(NULL),
    mBuffersCount(0),
    mVertexArrayObjectId(0),
    mChanges(kChangeNone),
    mAcceptsNewPrimitives(true),
    mClearPrimitives(false),
    mUpdatePassed(false)
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
    
void Batch::UpdateRenderData(ShadingInterface& shadingInterface) {
    if (mIsInvalid) {
        ClearRenderData();
        CreateRenderData(shadingInterface);
        mIsInvalid = false;
        mChanges = kChangeNone;
        mAcceptsNewPrimitives = false;
    }
    
    mUpdatePassed = true;
}

    
void Batch::AddPrimitive(Primitive& primitive)
{
    if (mUpdatePassed && mClearPrimitives) {
        mPrimitives.clear();
        mClearPrimitives = false;
        mAcceptsNewPrimitives = true;
    }

    if (mAcceptsNewPrimitives || primitive.isInvalid()) {
        if (size() == 0) {
            mOptions = primitive.mOptions;
        }
        primitive.mBatch = this;
        primitive.Validate();
        mPrimitives.push_back(&primitive);
        mIsInvalid = true;
    }
    
    

}
    
void Batch::Invalidate()
{
    if (mIsInvalid) return;
    
    mClearPrimitives = true;
    mUpdatePassed = false;
    
    Primitive::Invalidate();
}

    
}

