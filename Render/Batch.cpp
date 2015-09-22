
#include <Render/Batch.h>
#include <Render/BatchBucket.h>

namespace ftr {
    
Batch::Batch() :
    mRenderData(NULL),
    mBuffersCount(0),
    mVertexArrayObjectId(0)
{
//    std::cout << "Create \n";
}
    
Batch::~Batch()
{
//    std::cout << "Delete " << size() << "\n";
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
//        glDeleteBuffers(mBuffersCount, mBuffers);
//        glDeleteVertexArrays(1, &mVertexArrayObjectId);
    }
}

    
void Batch::AddPrimitive(Primitive& primitive)
{
    assert(AcceptsPrimitives());
    if (size() == 0) {
        mOptions = primitive.mOptions;
    }
    primitive.mBatch = this;
    primitive.Validate();
    
    mPrimitives.push_back(&primitive);
}
    
#pragma mark - Debug
    
std::string Batch::Description() const
{
    std::stringstream ss;
    ss << "size: " << size() << " invalid: " << (isInvalid() ? "YES" : "NO");
    return ss.str();
}
        
}

