
#pragma once

namespace ftr {
    
//
// Formats primitive data for GL
//
class Primitive
{
public:
    enum Type {
        kNode = 0,
        kLine,
        kPoint,
        kRect,
        kTriangle,
        kPolygon
    };
    
    Primitive(): mIsInvalid(true) {}
    virtual ~Primitive() {}
    
    virtual char* CreateRenderData() = 0;
    void Invalidate() { mIsInvalid = true; };
    
    virtual Type type() const { return kNode; }
    char* renderData();

private:
    bool mIsInvalid;
    char* mRenderData;
};
    

    
}

