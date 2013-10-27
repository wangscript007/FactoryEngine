
#pragma once

#include <Model/Node.h>
#include <Model/Octree.h>

namespace ftr {

class HalfEdge;
class PointNode : public Node
{
public:
    
    static const float c_fR;
    PointNode();
    PointNode(glm::vec3 origin);
    virtual ~PointNode();
    
    glm::vec3 mOrigin;
    
    virtual void Render(Layer& layer);
    virtual NodeType Type() const { return kPoint; }
    virtual void Transform(const glm::mat4& m4Transformation);
    Octree::Leaf* OctreeLeaf() const { return mOctreeLeaf; }
    void setOctreeLeaf(Octree::Leaf* leaf) { mOctreeLeaf = leaf; }
    void setActive(bool active) { mIsActive = active; }
    bool Active() const { return mIsActive; }
    
    void ConnectTo(PointNode* newNode);
    HalfEdge* mHalfEdge;
    HalfEdge* halfEdge() const { return mHalfEdge; }
    
private:
    
    Octree::Leaf* mOctreeLeaf;
    bool mIsActive;
    PointPrimitive primitive;
};
    
}

