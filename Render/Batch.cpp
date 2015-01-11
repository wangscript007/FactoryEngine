
#include <Render/Batch.h>
#include <Render/BatchBucket.h>

namespace ftr {
    
Batch::Batch() :
    mRenderData(NULL),
    mBuffersCount(0),
    mVertexArrayObjectId(0),
    mDeletePending(false)
{
    std::cout << "Create \n";
}
    
Batch::~Batch()
{
    std::cout << "Delete " << size() << "\n";
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
    if (mIsInvalid) {
        ClearRenderData();
        CreateRenderData(shadingInterface);
        mIsInvalid = false;
    }
}

    
void Batch::AddPrimitive(Primitive& primitive)
{
    assert(!mDeletePending);
    if (mIsInvalid) {
        if (size() == 0) {
            mOptions = primitive.mOptions;
        }
        primitive.mBatch = this;
        primitive.Validate();
        
        mPrimitives.push_back(&primitive);
    }
}
    
void Batch::Invalidate()
{
    mDeletePending = true;
    // Primitive can be invalidate in the middle of render
    // so allowing to clear only after rendering is comlete;
    
    Primitive::Invalidate();
}

    
#pragma mark - Debug
    
std::string Batch::Description() const
{
    std::stringstream ss;
    ss << "size: " << size() << " zombie: " << (isZombie() ? "YES" : "NO");
    return ss.str();
}
    
}

