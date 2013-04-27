
#include <Render/Primitive.h>

namespace ftr {

char* Primitive::renderData() {
    if (mIsInvalid) {
        mRenderData = CreateRenderData();
        mIsInvalid = false;
    }
    return mRenderData;
}
    
char* LinePrimitive::CreateRenderData()
{
    LinePrimitive::Data* data = reinterpret_cast<LinePrimitive::Data*>(new char[sizeof(LinePrimitive::Data)]);
    data->indices[0] = 0;
    data->indices[1] = 1;
    data->vertices[0].vec = mBegin;
    data->vertices[1].vec = mEnd;
    data->vertices[0].color = color;
    data->vertices[1].color = color;
    return reinterpret_cast<char*>(data);
}
    
    
}