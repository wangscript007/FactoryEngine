
#pragma once

#include "../Model/FTPoint.h"
#include "../Math/FTBox.h"

class FTOctree
{
public:
    class Node;
    
    struct Vec3 {
        float x, y, z;
    };
    
    
    FTOctree(FTBox sBox);
    ~FTOctree();
    
    void Render();
    void InsertPoint(FTPoint* pPoint);
    void RemovePoint(FTPoint* pPoint);
    Node* NodeContainingPoint(const O5Vec3& vPoint);
    
    enum NodeType { kBranch, kLeaf };
    
    class Node
    {
    public:
        typedef std::list<FTPoint*> TPointsList;
        
        struct SIndex {
            int m_iX, m_iY, m_iZ;
            SIndex() :m_iX(0), m_iY(0), m_iZ(0) {}
            SIndex(const int iX, const int iY, const int iZ)
            :m_iX(iX), m_iY(iY), m_iZ(iZ) {}
        };
        
        
        Node(FTBox sBox);
        ~Node() {};
        
        virtual void Render() const;
        NodeType Type() const { return kLeaf; }
        Node* Parent() const { return m_pParent; }
        void SetParent(Node* pParent)  { m_pParent = pParent; }
        FTBox& Box() { return m_sBox; }
        SIndex& Index() { return m_sIndex; }
        void SetIndex(SIndex sIndex) { m_sIndex = sIndex; }
        Node* NodeContainingPoint(const O5Vec3& vPoint);
        
    protected:
        FTBox m_sBox;
        Node* m_pParent;
        SIndex m_sIndex;
    private:
        
    };
    
    
    class Branch : public Node
    {
    public:
        Branch(FTBox sBox);
        ~Branch();
        
        void Render() const;
        NodeType Type() const { return kBranch; }
        Node* Child(int x, int y, int z) const { return m_pChildrenArray[x][y][z]; };
        void SetChild(int x, int y, int z, Node* pNode);
        void SetChild(SIndex& sIndex, Node* pNode);
    private:
        Node* m_pChildrenArray[2][2][2];
    };
    
    
    class Leaf : public Node
    {
    public:
        
        
        Leaf(FTBox sBox) : Node(sBox) {}
        ~Leaf() {};
        
        
        void Render() const;
        NodeType Type() const { return kLeaf; }
        void InsertPoint(FTPoint* pPoint);
        void RemovePoint(FTPoint* pPoint);
        unsigned long Size() const { return m_cPointsList.size(); }
        
    private:
        TPointsList m_cPointsList;
    };

private:
    FTOctree::Branch* Split(Leaf* pLeaf);
    void Merge(Branch* pBrach);
    
    Branch* m_pRootNode;
    int m_iMaxCapacity;
    int m_iMaxDepth;
};

