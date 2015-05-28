
#pragma once

#include <Geometry/GeometryPrimitives.h>
#include <Geometry/Cylinder.h>
#include <Graph/Node.h>

namespace ftr {

class PointNode;
    
class Octree : public Node
{
public:
    class Node;
    class Leaf;
    
    typedef std::list<PointNode*> TPointsList;
    
    struct Vertice3 {
        float x, y, z;
    };
    
    
    Octree(Box sBox);
    ~Octree();
    
    void Render(Layer& layer);
    void Invalidate(bool recursively);
    unsigned long Size();
    void InsertPoint(PointNode* pPoint);
    void RemovePoint(PointNode* pPoint);
    void UpdatePoint(PointNode* pPoint);
    Node* NodeContainingPoint(const glm::vec3& point);
    void PointNodesInBox(const Box& sBox, std::vector<PointNode*>& pointsVector) const;
    void PointNodes(std::vector<PointNode*>& pointsVector) const;
    void PointNodesInCylinder(const Cylinder& cylinder, std::vector<PointNode*>& pointsVector) const;
    
    enum Type { kBranch, kLeaf };
    
    class Node
    {
    public:
        
        struct SIndex {
            int x, y, z;
            SIndex() :x(0), y(0), z(0) {}
            SIndex(const int iX, const int iY, const int iZ)
            :x(iX), y(iY), z(iZ) {}
        };
        
        
        Node(Box sBox);
        virtual ~Node() {}
        
        virtual void Render(Layer& layer);
        virtual void Invalidate();
        
        virtual unsigned long Size() const { return 0; }
        Type Type() const { return m_eType; }
        Node* Parent() const { return mParent; }
        void setParent(Node* pParent)  { mParent = pParent; }
        Box& Box() { return mBox; }
        SIndex& Index() { return mIndex; }
        void setIndex(SIndex sIndex) { mIndex = sIndex; }
        Node* NodeContainingPoint(const glm::vec3& point);
        void PointNodes(std::vector<PointNode*>& pointsVector) const;
        void PointNodesInBox(const ftr::Box& sBox, std::vector<PointNode*>& pointsVector) const;
        void PointNodesInCylinder(const Cylinder& cylinder, std::vector<PointNode*>& pointsVector) const;
        void setDepth(int iDepth) { mDepth = iDepth; }
        int Depth() const { return mDepth; }
        
    protected:
        ftr::Box mBox;
        Node* mParent;
        SIndex mIndex;
        enum Type m_eType;
        int mDepth;
        
    private:
        
    };
    
    
    class Branch : public Node
    {
    public:
        Branch(struct Box sBox);
        virtual ~Branch();
        
        void Render(Layer& layer);
        void Invalidate();
        Node* Child(int x, int y, int z) const { return mChildrenArray[x][y][z]; };
        void setChild(int x, int y, int z, Node* pNode);
        void setChild(SIndex& sIndex, Node* pNode);
        unsigned long Size() const;
    private:
        Node* mChildrenArray[2][2][2];
    };
    
    
    class Leaf : public Node
    {
    public:
        
        
        Leaf(struct Box sBox) : Node(sBox) { m_eType = kLeaf; }
        void Invalidate();
        virtual ~Leaf() {}
        
        
        void Render(Layer& layer);
        unsigned long Size() const { return mPointsList.size(); }
        void InsertPoint(PointNode* pPoint);
        void RemovePoint(PointNode* pPoint);
        const TPointsList& PointNodes() const { return mPointsList; }
        
        std::string Description() const;
    private:
        TPointsList mPointsList;
        LinePrimitive linePrimitive[12];
    };
    
private:
    Octree::Branch* Split(Leaf* leaf);
    void Merge(Branch* brach);
    
    Branch* mRootNode;
    int mMaxCapacity;
    int mMaxDepth;
    bool mUpdateSize;
    unsigned long mSize;
    
    bool mIsInvalid;
};
    
}

