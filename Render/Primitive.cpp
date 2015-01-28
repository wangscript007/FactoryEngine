
#include <Render/Primitive.h>
#include <Render/PolygonBatch.h>
#include <Main/GLError.h>
#include <Geometry/Polygon.h>
#include <Geometry/Triangle.h>

namespace ftr {
    
const int DEPTH_MASK = 255<<8;
    
Primitive::Primitive() :
    mIsInvalid(true),
    mBatch(NULL),
    mOptions(kUseNone)
{
    
}
    
Primitive::~Primitive()
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

void Primitive::SetDepth(char depth)
{
    mOptions = mOptions & 255;
    mOptions |= depth<<8;
}
    
char Primitive::Depth() const
{
    return (mOptions & DEPTH_MASK) >> 8;
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
    
