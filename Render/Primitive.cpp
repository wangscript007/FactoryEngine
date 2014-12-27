
#include <Render/Primitive.h>
#include <Main/GLError.h>
#include <Geometry/Polygon.h>
#include <Geometry/Triangle.h>

namespace ftr {
    
Primitive::Primitive() :
    mIsInvalid(true),
    mOptions(kUseNone),
    mRenderData(NULL),
    mBuffersCount(0),
    mVertexArrayObjectId(0)
{
    
}

Primitive::~Primitive()
{
    ClearRenderData();
}
    
void Primitive::ClearRenderData()
{
    if(mRenderData) {
        delete[] mRenderData;
        mRenderData=NULL;
        glDeleteBuffers(mBuffersCount, mBuffers);
        glDeleteVertexArrays(1, &mVertexArrayObjectId);
        
    }
}


char* Primitive::renderData(ShadingInterface& shadingInterface) {
    if (mIsInvalid) {
        ClearRenderData();
        mRenderData = CreateRenderData(shadingInterface);
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
    data->vertices[0].vec = glm::vec4(mPosition.x,mPosition.y, mPosition.z, 0.0f);
    data->vertices[0].color = mColor;
    return reinterpret_cast<char*>(data);
}
        
char* LinePrimitive::CreateRenderData(ShadingInterface& shadingInterface)
{    
    LinePrimitive::Data* data = reinterpret_cast<LinePrimitive::Data*>(new char[sizeof(LinePrimitive::Data)]);
    data->vertices[0] = glm::vec4(mBegin.x,mBegin.y, mBegin.z, 1.0f);
    data->vertices[1] = glm::vec4(mEnd.x,mEnd.y, mEnd.z, 1.0f);
    data->colors[0] = mColor;
    data->colors[1] = mColor;
    
    const GLuint colorLoc = shadingInterface.colorLocation();
    const GLuint vertexLoc = shadingInterface.vertexLocation();
    
    
    glGenVertexArrays(1, &mVertexArrayObjectId);
    glBindVertexArray(mVertexArrayObjectId);
    
    mBuffersCount = 2;
    glGenBuffers(mBuffersCount, mBuffers);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*2, data->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*2, data->colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);
    return reinterpret_cast<char*>(data);
}
    
PolygonPrimitive::~PolygonPrimitive()
{
    
}
    
char* PolygonPrimitive::CreateRenderData(ShadingInterface& shadingInterface)
{
    Triangulate();
    unsigned long tz = mTriangles.size();
    glm::vec4* data = reinterpret_cast<glm::vec4*>(new char[sizeof(glm::vec4)*3*tz*4]);
    
    glm::vec4* vertices         = data;
    glm::vec4* normals          = data + (3 * tz);
    glm::vec4* colors           = data + (3 * tz * 2);
    glm::vec4* pickingColors    = data + (3 * tz * 3);
    
    
    glm::vec3 normal = mTriangles[0]->SurfaceNormal();
    
    for (int i = 0; i < mTriangles.size(); ++i) {
        for (int j = 0; j < 3; ++j) {
            *(vertices + (3*i + j))         = glm::vec4(mTriangles[i]->GetPoints()[j], 1.0f);
            *(normals + (3*i + j))          = glm::vec4(normal, 0.0f);
            *(colors + (3*i + j))           = mColor;
            *(pickingColors + (3*i + j))    = mPickingColor;
        }
    }
    
    const GLuint vertexLoc = shadingInterface.vertexLocation();
    const GLuint normalLoc = shadingInterface.normalLocation();
    const GLuint colorLoc = ShadingInterface::kColorAttributeIndex;
    const GLuint pickingColorLoc = ShadingInterface::kPickingColorAttributeIndex;
    
    glGenVertexArrays(1, &mVertexArrayObjectId);
    glBindVertexArray(mVertexArrayObjectId);
    
    mBuffersCount = 4;
    glGenBuffers(mBuffersCount, mBuffers);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*3*tz, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*3*tz, normals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(normalLoc);
    glVertexAttribPointer(normalLoc, 4, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*3*tz, colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*3*tz, pickingColors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(pickingColorLoc);
    glVertexAttribPointer(pickingColorLoc, 4, GL_FLOAT, 0, 0, 0);
    return reinterpret_cast<char*>(data);
}
    
}