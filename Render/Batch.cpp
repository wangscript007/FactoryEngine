
#include <Render/Batch.h>

namespace ftr {
    
Batch::Batch() :
    mRenderData(NULL),
    mBuffersCount(0),
    mVertexArrayObjectId(0)
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
    }
}

    
void Batch::AddPrimitive(Primitive& primitive)
{
    if (mIsInvalid) {
        if (size() == 0) {
            mOptions = primitive.mOptions;
        }
        primitive.mBatch = this;
        mPrimitives.push_back(&primitive);
    }
}
    
void Batch::Invalidate()
{
    if (mIsInvalid) return;
    
    Primitive::Invalidate();
    mPrimitives.clear();
}

    
}

