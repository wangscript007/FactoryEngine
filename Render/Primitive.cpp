
#include <Render/Primitive.h>

namespace ftr {

char* Primitive::renderData() {
    if (mIsInvalid) {
        mRenderData = CreateRenderData();
    }
    return mRenderData;
}
    
    
}