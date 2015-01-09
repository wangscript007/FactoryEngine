
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
        kUseLighting       = 1 << 3,
        
        kBatchFull          = 1 << 4,
        kBatchActive        = 1 << 5
    };
    
    
    Primitive();
    virtual ~Primitive();
    
    virtual void Invalidate();
    void Validate() { mIsInvalid = false; }
    
    
    virtual Type type() const { return kNone; }
    bool isInvalid() const { return mIsInvalid; }
    
    bool option(Option option) const { return (mOptions & static_cast<unsigned int>(option)) != 0; }
    void setOption(Option option, bool value);
    Batch* mBatch;
    unsigned int mOptions;
    
protected:
    bool mIsInvalid;
    
};

    
class PointPrimitive : public Primitive
{
public:
    PointPrimitive() {}
    virtual ~PointPrimitive() {}
    
    Type type() const { return kPoint; }
    glm::vec3 mPosition;
    glm::vec4 mColor;
};

    
class LinePrimitive : public Primitive
{
public:
    LinePrimitive() {};
    virtual ~LinePrimitive() {}
    
    Type type() const { return kLine; }
    glm::vec3 mBegin;
    glm::vec3 mEnd;
    glm::vec4 mColor;
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
};


}

