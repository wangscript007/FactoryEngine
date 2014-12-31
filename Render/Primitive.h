
#pragma once

#include <Shading/ShadingInterface.h>
#include <Geometry/Polygon.h>

namespace ftr {
    
class Batch;
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
    
    virtual void Invalidate();
    
    virtual Type type() const { return kNone; }
    void UpdateRenderData(ShadingInterface& shadingInterface);
    bool isInvalid() const { return mIsInvalid; }
    void setOption(Option option, bool value);
    
    bool option(Option option) const { return (mOptions & static_cast<unsigned int>(option)) != 0; }
    GLuint vertexArrayObjectId() const { return mVertexArrayObjectId; }
    Batch* mBatch;
    
protected:
    void ClearRenderData();
    virtual void CreateRenderData(ShadingInterface& shadingInterface) {}
    GLuint mVertexArrayObjectId;
    GLuint mBuffers[4];
    GLuint mBuffersCount;
    char* mRenderData;
    bool mIsInvalid;
    
private:
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
    void CreateRenderData();
    
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
    void CreateRenderData(ShadingInterface& shadingInterface);
    
private:
    
};
    
    
class PolygonPrimitive : public Primitive, public Polygon
{
public:
    PolygonPrimitive() {}
    PolygonPrimitive(const std::vector<glm::vec3>& vecs) : Polygon(vecs) {}
    virtual ~PolygonPrimitive() {}
    
    Type type() const { return kPolygon; }
    glm::vec4 mColor;
    glm::vec4 mPickingColor;
    
protected:
    void CreateRenderData(ShadingInterface& shadingInterface);
};


}

