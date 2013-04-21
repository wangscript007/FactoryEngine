
#include <Render/Primitive.h>

namespace ftr {

char* Primitive::renderData() {
    if (mIsInvalid) {
        mRenderData = CreateRenderData();
    }
    return mRenderData;
}
    
char* LinePrimitive::Primitive::CreateRenderData()
{
    LinePrimitive::Data* data = reinterpret_cast<LinePrimitive::Data*>(new char[sizeof(data)]);
    data->indices[0] = 0;
    data->indices[1] = 1;
    
    return reinterpret_cast<char*>(data);
}
    
    
}