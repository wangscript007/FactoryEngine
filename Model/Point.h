
#pragma once

#include <Model/Model.h>
#include <Model/Octree.h>

namespace ftr {

class Point : public Model
{
public:
    static const float c_fR;
    Point();
    Point(Vec3 origin);
    virtual ~Point() {}
    
    Vec3 mOrigin;
    
    virtual void Render();
    virtual NodeType Type() const { return kPoint; }
    virtual void Transform(const Mat4& m4Transformation);
    Octree::Leaf* OctreeLeaf() const { return mOctreeLeaf; }
    void setOctreeLeaf(Octree::Leaf* leaf) { mOctreeLeaf = leaf; }
    void setActive(bool active) { mIsActive = active; }
    bool Active() const { return mIsActive; }
    
    
private:
    Octree::Leaf* mOctreeLeaf;
    bool mIsActive;
};
    
}

