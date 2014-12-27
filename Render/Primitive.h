
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
        kTriangle,
        kPolygon
    };
    
    enum Option {
        kUseNone           = 0,
        kUseDepth          = 1 << 1,
        kUseBlend          = 1 << 2,
        kUseLighting       = 1 << 3
    };
    
    
    Primitive();
    virtual ~Primitive();
    
    void Invalidate() { mIsInvalid = true; }
    
    virtual Type type() const { return kNone; }
    char* renderData(ShadingInterface& shadingInterface);
    bool isInvalid() const { return mIsInvalid; }
    void setOption(Option option, bool value);
    bool option(Option option) const { return (mOptions & static_cast<unsigned int>(option)) != 0; }
    GLuint vertexArrayObjectId() const { return mVertexArrayObjectId; }
    
    
protected:
    void ClearRenderData();
    virtual char* CreateRenderData(ShadingInterface& shadingInterface) { return NULL; }
    GLuint mVertexArrayObjectId;
    GLuint mBuffers[4];
    GLuint mBuffersCount;
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
    
    LinePrimitive() {};
    virtual ~LinePrimitive() {}
    
    Type type() const { return kLine; }
    glm::vec3 mBegin;
    glm::vec3 mEnd;
    glm::vec4 mColor;

protected:
    char* CreateRenderData(ShadingInterface& shadingInterface);
    
private:
    
};
    
    
class PolygonPrimitive : public Primitive
{
public:
    struct Data {
        glm::vec4 vertices[3];
        glm::vec4 normals[3];
        glm::vec4 colors[3];
        glm::vec4 pickingColors[3];
    };
    
    PolygonPrimitive() {}
    PolygonPrimitive(const std::vector<glm::vec3>& vecs) { mVec = vecs; }
    virtual ~PolygonPrimitive();
    
    Type type() const { return kPolygon; }
    std::vector<glm::vec3> mVec;
    glm::vec4 mColor;
    glm::vec4 mPickingColor;
    
    std::vector<PolygonPrimitive*>mSubpolygons;
protected:
    char* CreateRenderData(ShadingInterface& shadingInterface);
    
private:
    void AssignSurfaceNormals(PolygonPrimitive::Data* data);

    
private:
    
};


}

