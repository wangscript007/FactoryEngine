
#pragma once

#include <Math/Geometry.h>

namespace ftr {

class PointNode;
    
class Octree
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
    
    void Render();
    unsigned long Size();
    void InsertPoint(PointNode* pPoint);
    void RemovePoint(PointNode* pPoint);
    void UpdatePoint(PointNode* pPoint);
    Node* NodeContainingPoint(const Vec3& point);
    void PointNodesInBox(const Box& sBox, std::vector<PointNode*>& pointsVector) const;
    
    
    enum NodeType { kBranch, kLeaf };
    
    class Node
    {
    public:
        
        struct SIndex {
            int mX, mY, mZ;
            SIndex() :mX(0), mY(0), mZ(0) {}
            SIndex(const int iX, const int iY, const int iZ)
            :mX(iX), mY(iY), mZ(iZ) {}
        };
        
        
        Node(Box sBox);
        virtual ~Node() {}
        
        virtual void Render() const;
        virtual unsigned long Size() const { return 0; }
        NodeType Type() const { return m_eType; }
        Node* Parent() const { return mParent; }
        void setParent(Node* pParent)  { mParent = pParent; }
        Box& Box() { return mBox; }
        SIndex& Index() { return mIndex; }
        void setIndex(SIndex sIndex) { mIndex = sIndex; }
        Node* NodeContainingPoint(const Vec3& point);
        void PointNodesInBox(const ftr::Box& sBox, std::vector<PointNode*>& pointsVector) const;
        void setDepth(int iDepth) { mDepth = iDepth; }
        int Depth() const { return mDepth; }
        
    protected:
        ftr::Box mBox;
        Node* mParent;
        SIndex mIndex;
        NodeType m_eType;
        int mDepth;
    private:
        
    };
    
    
    class Branch : public Node
    {
    public:
        Branch(struct Box sBox);
        virtual ~Branch();
        
        void Render() const;
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
        virtual ~Leaf() {}
        
        
        void Render() const;
        unsigned long Size() const { return mPointsList.size(); }
        void InsertPoint(PointNode* pPoint);
        void RemovePoint(PointNode* pPoint);
        const TPointsList& PointNodes() const { return mPointsList; }
    private:
        TPointsList mPointsList;
    };
    
private:
    Octree::Branch* Split(Leaf* leaf);
    void Merge(Branch* brach);
    
    Branch* mRootNode;
    int mMaxCapacity;
    int mMaxDepth;
    bool mUpdateSize;
    unsigned long mSize;
};
    
}

