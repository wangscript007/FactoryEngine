
#pragma once

#include <Math/FTGeometry.h>

class FTPoint;
class FTOctree
{
public:
    class Node;
    class Leaf;
    
    typedef std::list<FTPoint*> TPointsList;
    
    struct Vec3 {
        float x, y, z;
    };
    
    
    FTOctree(FTBox sBox);
    ~FTOctree();
    
    void Render();
    unsigned long Size();
    void InsertPoint(FTPoint* pPoint);
    void RemovePoint(FTPoint* pPoint, Leaf* pLeaf = NULL);
    void UpdatePoint(FTPoint* pPoint);
    Node* NodeContainingPoint(const O5Vec3& vPoint);
    void PointsInBox(const FTBox& sBox, std::vector<FTPoint*>& rPointsVector) const;
    
    
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
        
        
        Node(FTBox sBox);
        ~Node() {};
        
        virtual void Render() const;
        virtual unsigned long Size() const { return 0; }
        NodeType Type() const { return m_eType; }
        Node* Parent() const { return m_pParent; }
        void SetParent(Node* pParent)  { m_pParent = pParent; }
        FTBox& Box() { return m_sBox; }
        SIndex& Index() { return m_sIndex; }
        void SetIndex(SIndex sIndex) { m_sIndex = sIndex; }
        Node* NodeContainingPoint(const O5Vec3& vPoint);
        void PointsInBox(const FTBox& sBox, std::vector<FTPoint*>& rPointsVector) const;
        void SetDepth(int iDepth) { m_iDepth = iDepth; }
        int Depth() const { return m_iDepth; }
        
    protected:
        FTBox m_sBox;
        Node* m_pParent;
        SIndex m_sIndex;
        NodeType m_eType;
        int m_iDepth;
    private:
        
    };
    
    
    class Branch : public Node
    {
    public:
        Branch(FTBox sBox);
        ~Branch() {};
        
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
        
        
        Leaf(FTBox sBox) : Node(sBox) { m_eType = kLeaf; }
        ~Leaf() {};
        
        
        void Render() const;
        unsigned long Size() const { return m_cPointsList.size(); }
        void InsertPoint(FTPoint* pPoint);
        void RemovePoint(FTPoint* pPoint);
        const TPointsList& Points() const { return m_cPointsList; }
    private:
        TPointsList m_cPointsList;
    };
    
private:
    FTOctree::Branch* Split(Leaf* pLeaf);
    void Merge(Branch* pBrach);
    
    Branch* m_pRootNode;
    int m_iMaxCapacity;
    int m_iMaxDepth;
    bool m_bUpdateSize;
    unsigned long m_iSize;
};

