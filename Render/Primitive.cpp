
#include <Render/Primitive.h>
#include <Main/GLError.h>

namespace ftr {

char* Primitive::renderData(ShadersInput& shadersInput) {
    if (mIsInvalid) {
        mRenderData = CreateRenderData(shadersInput);
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
    
    
    
char* PointPrimitive::CreateRenderData()
{
    PointPrimitive::Data* data = reinterpret_cast<PointPrimitive::Data*>(new char[sizeof(PointPrimitive::Data)]);
    data->indices[0] = 0;
    data->vertices[0].vec = mPosition;
    data->vertices[0].color = mColor;
    return reinterpret_cast<char*>(data);
}
    
    
char* LinePrimitive::CreateRenderData(ShadersInput& shadersInput)
{    
    LinePrimitive::Data* data = reinterpret_cast<LinePrimitive::Data*>(new char[sizeof(LinePrimitive::Data)]);
    data->vertices[0] = Vec4(mBegin);
    data->vertices[1] = Vec4(mEnd);
    data->colors[0] = color;
    data->colors[1] = color;
    
    const GLuint colorLoc = shadersInput.colorLocation();
    const GLuint vertexLoc = shadersInput.vertexLocation();
    
    glGenVertexArrays(1, &mVertexArrayObjectId);
    glBindVertexArray(mVertexArrayObjectId);
    
    GLuint buffers[2];
    glGenBuffers(2, buffers);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec4)*2, data->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color4f)*2, data->colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);
    return reinterpret_cast<char*>(data);
}
    
    
RectanglePrimitive::RectanglePrimitive()
{
    setOption(kUseLighting, true);
    setOption(kUseDepth, true);
}
    
    
char* RectanglePrimitive::CreateRenderData(ShadersInput& shadersInput)
{
    RectanglePrimitive::Data* data = reinterpret_cast<RectanglePrimitive::Data*>(new char[sizeof(RectanglePrimitive::Data)]);
    
    data->vertices[0] = Vec4(mVec[0]);
    data->vertices[1] = Vec4(mVec[1]);
    data->vertices[3] = Vec4(mVec[2]);
    data->vertices[2] = Vec4(mVec[3]);
    
    AssignSurfaceNormals(data);
    for(int i = 0; i < 4; ++i) {
        data->colors[i] = color;
    }
    
    const GLuint colorLoc = shadersInput.colorLocation();
    const GLuint vertexLoc = shadersInput.vertexLocation();
    const GLuint normalLoc = shadersInput.normalLocation();
    
    glGenVertexArrays(1, &mVertexArrayObjectId);
    glBindVertexArray(mVertexArrayObjectId);
    
    GLuint buffers[3];
    glGenBuffers(3, buffers);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec4)*4, data->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec4)*4, data->normals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(normalLoc);
    glVertexAttribPointer(normalLoc, 4, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color4f)*4, data->colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);

    return reinterpret_cast<char*>(data);
}
    
void RectanglePrimitive::AssignSurfaceNormals(RectanglePrimitive::Data* data)
{
    Vec4 normal;
    normal.Zero();
    static const int vertexCount = 3;
    for (int i = 0; i < vertexCount; i++) {
        Vec4& current = data->vertices[i];
        Vec4& next = data->vertices[(i+1)%vertexCount];
        normal.mX = normal.mX + (current.mY - next.mY) * (current.mZ + next.mZ);
        normal.mY = normal.mY + (current.mZ - next.mZ) * (current.mX + next.mX);
        normal.mZ = normal.mZ + (current.mX - next.mX) * (current.mY + next.mY);
    }
    normal.Normalize();
    for (int i = 0; i < vertexCount+1; i++) {
        data->normals[i] = normal;
    }
}

    
    
    
    
    
char* PolygonPrimitive::CreateRenderData(ShadersInput& shadersInput)
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