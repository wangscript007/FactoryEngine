
#include <Render/Primitive.h>

namespace ftr {

char* Primitive::renderData() {
    if (mIsInvalid) {
        mRenderData = CreateRenderData();
        mIsInvalid = false;
    }
    return mRenderData;
}
    
void Primitive::setOption(Option option, bool value)
{
    if (value) {
        mOptions |= static_cast<unsigned int>(option);
    } else {
        mOptions &= ~(static_cast<unsigned int>(option));
    }
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
    
    
RectanglePrimitive::RectanglePrimitive()
{
    setOption(kUseLighting, true);
    setOption(kUseDepth, true);
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
    data->vertices[0].color = color;
    data->vertices[1].color = color;
    data->vertices[2].color = color;
    data->vertices[3].color = color;
    AssignSurfaceNormals(data);
    return reinterpret_cast<char*>(data);
}
    
void RectanglePrimitive::AssignSurfaceNormals(RectanglePrimitive::Data* data)
{
    Vec3 normal;
    normal.Zero();
    static const int vertexCount = 4;
    for (int i = 0; i < vertexCount; i++) {
        Vec3& current = data->vertices[i].vec;
        Vec3& next = data->vertices[(i+1)%vertexCount].vec;
        normal.mX = normal.mX + (current.mY - next.mY) * (current.mZ + next.mZ);
        normal.mY = normal.mY + (current.mZ - next.mZ) * (current.mX + next.mX);
        normal.mZ = normal.mZ + (current.mX - next.mX) * (current.mY + next.mY);
    }
    normal.Normalize();
    for (int i = 0; i < vertexCount; i++) {
        data->vertices[i].normal = normal;
    }

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