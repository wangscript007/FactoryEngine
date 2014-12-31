
#include <Render/Batch.h>

namespace ftr {
    
void Batch::AddPrimitive(Primitive& primitive)
{
    if (mIsInvalid) {
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

