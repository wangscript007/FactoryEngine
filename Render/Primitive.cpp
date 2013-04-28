
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
    
char* RectanglePrimitive::CreateRenderData()
{
    RectanglePrimitive::Data* data = reinterpret_cast<RectanglePrimitive::Data*>(new char[sizeof(RectanglePrimitive::Data)]);
    data->indices[0] = 0;
    data->indices[1] = 1;
    data->indices[2] = 2;
    data->indices[3] = 3;
    data->vertices[0].vec = mVec[0];
    data->vertices[1].vec = mVec[1];
    data->vertices[2].vec = mVec[2];
    data->vertices[3].vec = mVec[3];
    //data->vertices[3].vec = mVec[0] + (mVec[1] - mVec[2]);
    data->vertices[0].color = color;
    data->vertices[1].color = color;
    data->vertices[2].color = color;
    data->vertices[3].color = color;
    return reinterpret_cast<char*>(data);
}

    
char* PolygonPrimitive::CreateRenderData()
{
    PolygonPrimitive::Data* data = reinterpret_cast<PolygonPrimitive::Data*>(new char[sizeof(PolygonPrimitive::Data)]);
    data->indices[0] = 0;
    data->indices[1] = 1;
    data->indices[2] = 2;
    data->indices[3] = 3;
   
    data->vertices[0].color = color;
    data->vertices[1].color = color;
    return reinterpret_cast<char*>(data);
}

}