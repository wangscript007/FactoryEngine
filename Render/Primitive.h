
#pragma once

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
    
    
    Primitive(): mIsInvalid(true), mOptions(kUseNone) {}
    virtual ~Primitive() {
        if(mRenderData) {
            delete[] mRenderData;
            mRenderData=0;
        }
    }
    
    void Invalidate() { mIsInvalid = true; }
    
    virtual Type type() const { return kNone; }
    char* renderData();
    bool isInvalid() const { return mIsInvalid; }
    void setOption(Option option, bool value);
    bool option(Option option) const { return (mOptions & static_cast<unsigned int>(option)) != 0; }
    GLuint vertexArrayObjectId() const { return mVertexArrayObjectId; }
    
protected:
    virtual char* CreateRenderData() { return NULL; }
    GLuint mVertexArrayObjectId;
    char* mRenderData;
    
private:
    
    bool mIsInvalid;
    unsigned int mOptions;
    
};


struct Vertex {
    Vec3 vec;
    Vec3 normal;
    Color4f color;
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
    Vec3 mPosition;
    Color4f mColor;
    
protected:
    char* CreateRenderData();
    
private:
    
};

    
class LinePrimitive : public Primitive
{
public:
    struct Data {
        Vertex vertices[2];
    };
    
    LinePrimitive() {}
    virtual ~LinePrimitive() {}
    
    Type type() const { return kLine; }
    Vec3 mBegin;
    Vec3 mEnd;
    Color4f color;
protected:
    char* CreateRenderData();
    
private:
    
};
    
    
class RectanglePrimitive : public Primitive
{
public:
    struct Data {
        Vec4 vertices[3];
    };
    
    RectanglePrimitive();
    virtual ~RectanglePrimitive() {}
    
    Type type() const { return kRectangle; }
    Vec3 mVec[4];
    Color4f color;
protected:
    char* CreateRenderData();
    
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
    Vec3 mNormal;
    Vec3 mCenter;
    Vec2 mSize;
    Color4f color;
protected:
    char* CreateRenderData();
    
private:
    
};


}

