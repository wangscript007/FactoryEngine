
#pragma once

#include <Model/Node.h>
#include <Model/Octree.h>

namespace ftr {

class PointNode : public Node
{
public:
    static const float c_fR;
    PointNode();
    PointNode(Vec3 origin);
    virtual ~PointNode() {}
    
    Vec3 mOrigin;
    
    virtual void Render(RenderBundle& renderBundle);
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

