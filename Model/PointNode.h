
#pragma once

#include <Model/Node.h>
#include <Processing/Octree.h>
#include <Processing/PointNodeIterator.h>


namespace ftr {

class Edge;
class FaceNode;
class FaceTraversal;
class PointNodeIterator;
    
class PointNode : public Node
{
public:
    typedef PointNodeIterator Iterator;
    
    struct ConnectionResult {
        FaceNode* faces[2];
        Edge* edge;
        ConnectionResult() : edge(NULL) { faces[0] = NULL; faces[1] = NULL; };
    };
    
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
    
    ConnectionResult ConnectTo(PointNode* other, bool skipTraversal = false);
    Edge* mEdge;
    ftr::Edge* FindOutgoingFreeEdge() const;
    
    PointNode::Iterator Begin() const;
    PointNode::Iterator End() const;
    PointNode::Iterator IteratorFromEdge(Edge* edge) const;
    
    void Insert(Iterator position, ftr::Edge& edge);
    void Remove(Iterator position);
    void Move(Iterator fromPosition, Iterator toPosition);
    void Move(Edge& edge, Iterator position);
    bool IsEmpty() const { return mEdge == NULL; };
    
    std::string Description() const;
    std::string mName;
    
private:
    Octree::Leaf* mOctreeLeaf;
    bool mIsActive;
    PointPrimitive primitive;
};
    
}

