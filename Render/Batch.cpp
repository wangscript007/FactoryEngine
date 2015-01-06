
#include <Render/Batch.h>

namespace ftr {
    
const int kSizeLimit = 10000;
    
    
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
        if (size() > kSizeLimit) {
            setFull(true);
        }
        mIsInvalid = true;
    }
}
    
void Batch::ClearPrimitives()
{
    if (mPrimitivesClearAllowed && mPrimitivesClearPending) {
        mPrimitives.clear();
        setFull(false);
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

