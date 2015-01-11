
#include <Render/Batch.h>
#include <Render/BatchBucket.h>

namespace ftr {
    
Batch::Batch() :
    mRenderData(NULL),
    mBuffersCount(0),
    mVertexArrayObjectId(0),
    mAcceptsValidPrimitives(true),
    mPrimitivesClearPending(false),
    mPrimitivesClearAllowed(false)
{
    std::cout << "Create \n";
}
    
Batch::~Batch()
{
    std::cout << "Delete \n";
    if (mPrimitives.size()) {
        for (auto& primitive : mPrimitives) {
            if (primitive->mBatch == this) {
                primitive->mBatch = NULL;
            }
        }
    }
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
    
bool Batch::ClearPrimitives()
{
    if (mPrimitivesClearAllowed && mPrimitivesClearPending) {
        mPrimitives.clear();
        mPrimitivesClearPending = false;
        mAcceptsValidPrimitives = true;
    }
    return true;
}
    
    
void Batch::Invalidate()
{
    if (mIsInvalid) return;
    
    mPrimitivesClearPending = true;
    // Primitive can be invalidate in the middle of render
    // so allowing to clear only after rendering is comlete
    mPrimitivesClearAllowed = false;
    
    Primitive::Invalidate();
}

    
}

