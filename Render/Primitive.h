
#pragma once

#include <Shading/ShadingInterface.h>

namespace ftr {
//
// Formats primitive data for GL
//
class Primitive
{
public:
    enum Type {
        kNone = 0,
        kPoint,
        kLine,
        kRectangle,
        kTriangle,
        kPolygon
    };
    
    enum Option {
        kUseNone           = 0,
        kUseDepth          = 1 << 1,
        kUseBlend          = 1 << 2,
        kUseLighting       = 1 << 3
    };
    
    
    Primitive(): mIsInvalid(true), mOptions(kUseNone), mRenderData(NULL) {}
    virtual ~Primitive() {
        if(mRenderData) {
            delete[] mRenderData;
            mRenderData=0;
        }
    }
    
    void Invalidate() { mIsInvalid = true; }
    
    virtual Type type() const { return kNone; }
    char* renderData(ShadingInterface& shadingInterface);
    bool isInvalid() const { return mIsInvalid; }
    void setOption(Option option, bool value);
    bool option(Option option) const { return (mOptions & static_cast<unsigned int>(option)) != 0; }
    GLuint vertexArrayObjectId() const { return mVertexArrayObjectId; }
    
protected:
    virtual char* CreateRenderData(ShadingInterface& shadingInterface) { return NULL; }
    GLuint mVertexArrayObjectId;
    char* mRenderData;
    
private:
    
    bool mIsInvalid;
    unsigned int mOptions;
    
};


struct Vertex {
    glm::vec4 vec;
    glm::vec4 normal;
    glm::vec4 color;
};

    
class PointPrimitive : public Primitive
{
public:
    struct Data {
        Vertex vertices[1];
        GLubyte indices[1];
    };
    
    PointPrimitive() {}
    virtual ~PointPrimitive() {}
    
    Type type() const { return kPoint; }
    glm::vec3 mPosition;
    glm::vec4 mColor;
    
protected:
    char* CreateRenderData();
    
private:
    
};

    
class LinePrimitive : public Primitive
{
public:
    struct Data {
        glm::vec4 vertices[2];
        glm::vec4 colors[2];
    };
    
    LinePrimitive() {}
    virtual ~LinePrimitive() {}
    
    Type type() const { return kLine; }
    glm::vec3 mBegin;
    glm::vec3 mEnd;
    glm::vec4 color;
protected:
    char* CreateRenderData(ShadingInterface& shadingInterface);
    
private:
    
};
    
    
class RectanglePrimitive : public Primitive
{
public:
    struct Data {
        glm::vec4 vertices[4];
        glm::vec4 normals[4];
        glm::vec4 colors[4];
        glm::vec4 pickingColors[4];
    };
    
    RectanglePrimitive();
    virtual ~RectanglePrimitive() {}
    
    Type type() const { return kRectangle; }
    glm::vec3 mVec[4];
    glm::vec4 color;
    glm::vec4 mPickingColor;
protected:
    char* CreateRenderData(ShadingInterface& shadingInterface);
    
private:
    void AssignSurfaceNormals(RectanglePrimitive::Data* data);
    
};

    
class PolygonPrimitive : public Primitive
{
public:
    struct Data {
        Vertex vertices[4];
        GLubyte indices[4];
    };
    
    PolygonPrimitive() {}
    virtual ~PolygonPrimitive() {}
    
    Type type() const { return kPolygon; }
    glm::vec3 mNormal;
    glm::vec3 mCenter;
    glm::vec2 mSize;
    glm::vec4 color;
protected:
    char* CreateRenderData(ShadingInterface& shadingInterface);
    
private:
    
};


}

