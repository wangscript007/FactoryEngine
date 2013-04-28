
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
        kLine,
        kPoint,
        kRectangle,
        kTriangle,
        kPolygon
    };
    
    Primitive(): mIsInvalid(true) {}
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
    
protected:
    virtual char* CreateRenderData() { return NULL; };

    char* mRenderData;
private:
    bool mIsInvalid;
    
};


struct Vertex {
    Vec3 vec;
    Vec3 normal;
    Color4f color;
};
    
    
class LinePrimitive : public Primitive
{
public:
    struct Data {
        Vertex vertices[2];
        GLubyte indices[2];
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
        Vertex vertices[4];
        GLubyte indices[4];
    };
    
    RectanglePrimitive() {}
    virtual ~RectanglePrimitive() {}
    
    Type type() const { return kRectangle; }
    Vec3 mVec[4];
    Color4f color;
protected:
    char* CreateRenderData();
    
private:
    
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

