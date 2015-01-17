
#pragma once

#include <Graph/Node.h>
#include <Processing/Octree.h>

namespace ftr {

class FaceNode;
class FaceTraversal;
class PointNodeIterator;
    
class PointNode : public Node
{
public:
    virtual enum Type Type() const { return kPoint; }
    
    typedef PointNodeIterator Iterator;
    
    static const float c_fR;
    PointNode();
    PointNode(glm::vec3 origin);
    virtual ~PointNode();
    
    glm::vec3 mOrigin;
    glm::vec3 Center() const { return mOrigin; }
    
    virtual void Render(Layer& layer);
    virtual void Invalidate(bool recursively);
    virtual void Transform(const glm::mat4& m4Transformation);
    void PointNodes(std::vector<Node*>& result);
    Octree::Leaf* OctreeLeaf() const { return mOctreeLeaf; }
    void setOctreeLeaf(Octree::Leaf* leaf) { mOctreeLeaf = leaf; }
    bool OctreeLeafIsInvalid() const;
    void setActive(bool active) { mIsActive = active; }
    bool Active() const { return mIsActive; }
    
    std::string Description() const;
    std::string mName;
    
    bool mVisited;
    
private:
    Octree::Leaf* mOctreeLeaf;
    bool mIsActive;
    PointPrimitive primitive;
};
    
}

