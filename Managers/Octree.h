
#pragma once

#include <Math/Geometry.h>

namespace Factory {

class Point;
    
class Octree
{
public:
    class Node;
    class Leaf;
    
    typedef std::list<Point*> TPointsList;
    
    struct Vec3 {
        float x, y, z;
    };
    
    
    Octree(Box sBox);
    ~Octree();
    
    void Render();
    unsigned long Size();
    void InsertPoint(Point* pPoint);
    void RemovePoint(Point* pPoint);
    void UpdatePoint(Point* pPoint);
    Node* NodeContainingPoint(const O5Vec3& vPoint);
    void PointsInBox(const Box& sBox, std::vector<Point*>& rPointsVector) const;
    
    
    enum NodeType { kBranch, kLeaf };
    
    class Node
    {
    public:
        
        struct SIndex {
            int m_iX, m_iY, m_iZ;
            SIndex() :m_iX(0), m_iY(0), m_iZ(0) {}
            SIndex(const int iX, const int iY, const int iZ)
            :m_iX(iX), m_iY(iY), m_iZ(iZ) {}
        };
        
        
        Node(Box sBox);
        virtual ~Node() {}
        
        virtual void Render() const;
        virtual unsigned long Size() const { return 0; }
        NodeType Type() const { return m_eType; }
        Node* Parent() const { return m_pParent; }
        void SetParent(Node* pParent)  { m_pParent = pParent; }
        Box& Box() { return m_sBox; }
        SIndex& Index() { return m_sIndex; }
        void SetIndex(SIndex sIndex) { m_sIndex = sIndex; }
        Node* NodeContainingPoint(const O5Vec3& vPoint);
        void PointsInBox(const Factory::Box& sBox, std::vector<Point*>& rPointsVector) const;
        void SetDepth(int iDepth) { m_iDepth = iDepth; }
        int Depth() const { return m_iDepth; }
        
    protected:
        Factory::Box m_sBox;
        Node* m_pParent;
        SIndex m_sIndex;
        NodeType m_eType;
        int m_iDepth;
    private:
        
    };
    
    
    class Branch : public Node
    {
    public:
        Branch(struct Box sBox);
        virtual ~Branch();
        
        void Render() const;
        Node* Child(int x, int y, int z) const { return m_pChildrenArray[x][y][z]; };
        void SetChild(int x, int y, int z, Node* pNode);
        void SetChild(SIndex& sIndex, Node* pNode);
        unsigned long Size() const;
    private:
        Node* m_pChildrenArray[2][2][2];
    };
    
    
    class Leaf : public Node
    {
    public:
        
        
        Leaf(struct Box sBox) : Node(sBox) { m_eType = kLeaf; }
        virtual ~Leaf() {}
        
        
        void Render() const;
        unsigned long Size() const { return m_cPointsList.size(); }
        void InsertPoint(Point* pPoint);
        void RemovePoint(Point* pPoint);
        const TPointsList& Points() const { return m_cPointsList; }
    private:
        TPointsList m_cPointsList;
    };
    
private:
    Octree::Branch* Split(Leaf* pLeaf);
    void Merge(Branch* pBrach);
    
    Branch* m_pRootNode;
    int m_iMaxCapacity;
    int m_iMaxDepth;
    bool m_bUpdateSize;
    unsigned long m_iSize;
};
    
}

