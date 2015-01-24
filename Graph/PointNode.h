
#pragma once

#include <Graph/Node.h>
#include <Graph/Vertex.h>
#include <Processing/Octree.h>

namespace ftr {

class FaceNode;
class FaceTraversal;
class Vertex;
    
    
class PointNode : public Node
{
public:
    virtual enum Type Type() const { return kPoint; }
    
    static const float c_fR;
    PointNode();
    PointNode(glm::vec3 origin);
    virtual ~PointNode();
    
    glm::vec3 Center() const { return Origin(); }
    const glm::vec3& Origin() const { return mVertex.mOrigin; }
    void SetOrigin(glm::vec3 origin) { mVertex.mOrigin = origin; }
    
    virtual void Render(Layer& layer);
    virtual void Invalidate(bool recursively);
    virtual void Transform(const glm::mat4& m4Transformation);
    void PointNodes(std::vector<Node*>& result);
    
    Octree::Leaf* OctreeLeaf() const { return mOctreeLeaf; }
    void setOctreeLeaf(Octree::Leaf* leaf) { mOctreeLeaf = leaf; }
    bool OctreeLeafIsInvalid() const;
    
    std::string Description() const;
    std::string mName;
    bool mIsActive;
    
    bool IsConnectedTo(const PointNode& target);
    Vertex& vertex() { return mVertex; }
    
private:
    
    
    Vertex mVertex;
    Octree::Leaf* mOctreeLeaf;
    
    PointPrimitive primitive;
};
    
}

