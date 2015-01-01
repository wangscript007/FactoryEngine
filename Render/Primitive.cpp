
#include <Render/Primitive.h>
#include <Render/PolygonBatch.h>
#include <Main/GLError.h>
#include <Geometry/Polygon.h>
#include <Geometry/Triangle.h>

namespace ftr {
    
Primitive::Primitive() :
    mIsInvalid(true),
    mBatch(NULL),
    mOptions(kUseNone)
{
    
}
    
void Primitive::Invalidate()
{
    mIsInvalid = true;
    if (mBatch) {
        mBatch->Invalidate();
        mBatch = NULL;
    }
}
    
void Primitive::setOption(Option option, bool value)
{
    if (value) {
        mOptions |= static_cast<unsigned int>(option);
    } else {
        mOptions &= ~(static_cast<unsigned int>(option));
    }
}

}
    
