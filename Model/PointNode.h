
#pragma once

#include <Model/Node.h>
#include <Model/Octree.h>
//#include <Model/PointNodeIterator.h>


namespace ftr {

class Edge;
class FaceNode;
class FaceTraversal;
class PointNodeIterator;
    
class PointNode : public Node
{
public:
    typedef PointNodeIterator Iterator;
    
    typedef struct {
        FaceNode* faceA;
        FaceNode* faceB;
        Edge* edge;
    } ConnectionResult;
    
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
    void Insert(Iterator position, ftr::Edge& edge);
    void Remove(Iterator position);
    
    
    
    std::string mName;
    
private:
    Octree::Leaf* mOctreeLeaf;
    bool mIsActive;
    PointPrimitive primitive;
};
    
}

