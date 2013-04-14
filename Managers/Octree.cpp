
#include <Managers/Octree.h>
#include <Model/Point.h>
#include <Main/GLError.h>

namespace Factory {

Octree::Octree(Box sBox)
    :m_iMaxCapacity(2)
    ,m_iMaxDepth(9)
    ,m_iSize(0)
    ,m_bUpdateSize(true)

{
    m_pRootNode = Split(new Leaf(sBox));
}

Octree::~Octree()
{
    FT_DELETE(m_pRootNode);
}

#pragma mark Instance

void Octree::Render()
{
    return;
    static_cast<Node*>(m_pRootNode)->Render();
}


Octree::Branch* Octree::Split(Octree::Leaf *pLeaf)
{
    if (pLeaf->Depth() >= m_iMaxDepth) {
        return NULL;
    }
    unsigned long iInitialCount = pLeaf->Size();
    unsigned long iCounter = 0;
    TPointsList cPointsList = pLeaf->Points();
    Branch* pBranch =  new Branch(pLeaf->Box());
    if (pLeaf->Parent()) {
        assert(pLeaf->Parent()->Type() == kBranch);
        static_cast<Branch*>(pLeaf->Parent())->SetChild(pLeaf->Index(), pBranch);
    }
    Leaf* pChildLeaf;
    Box sBox = pLeaf->Box();
    O5Vec3 vHalf = sBox.m_vHalfDimention/2.0f;
    O5Vec3 vCenter;
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                if (x == 0) {
                    vCenter.m_fX = sBox.m_vCenter.m_fX - vHalf.m_fX;
                } else {
                    vCenter.m_fX = sBox.m_vCenter.m_fX + vHalf.m_fX;
                }
                if (y == 0) {
                    vCenter.m_fY = sBox.m_vCenter.m_fY - vHalf.m_fY;
                } else {
                    vCenter.m_fY = sBox.m_vCenter.m_fY + vHalf.m_fY;
                }
                if (z == 0) {
                    vCenter.m_fZ = sBox.m_vCenter.m_fZ - vHalf.m_fZ;
                } else {
                    vCenter.m_fZ = sBox.m_vCenter.m_fZ + vHalf.m_fZ;
                }
                pChildLeaf = new Leaf(Box(vCenter, vHalf));
                for(auto i = cPointsList.begin(); i != cPointsList.end(); ++i) {
                    if (pChildLeaf->Box().Contains((*i)->m_vOrigin)) {
                        pChildLeaf->InsertPoint(*i);
                        iCounter++;
                    }
                }
                pBranch->SetChild(x, y, z, pChildLeaf);
                if (pChildLeaf->Size() > m_iMaxCapacity) {
                    Split(pChildLeaf);
                }
            }
        }
    }
    assert(iCounter == iInitialCount);
    FT_DELETE(pLeaf);
    m_bUpdateSize = true;
    return pBranch;
}

void Octree::Merge(Branch* pBranch)
{
    if (pBranch == m_pRootNode) {
        return;
    }
    assert(pBranch->Type() == kBranch);
    Leaf* pLeaf = new Leaf(pBranch->Box());
    if (pBranch->Parent()) {
        assert(pBranch->Parent()->Type() == kBranch);
        static_cast<Branch*>(pBranch->Parent())->SetChild(pBranch->Index(), pLeaf);
    }
    TPointsList cPointsList;
    Leaf* pChildLeaf;
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                pChildLeaf = static_cast<Leaf*>(pBranch->Child(x, y, z));
                cPointsList = pChildLeaf->Points();
                for(auto i = cPointsList.begin(); i != cPointsList.end(); ++i) {
                    pLeaf->InsertPoint((*i));
                }
            }
        }
    }
    Branch* pParent = static_cast<Branch*>(pBranch->Parent());
    if (pParent) {
        if (pParent->Size() <= m_iMaxCapacity) {
            Merge(pParent);
        }
    }
    FT_DELETE(pBranch);
}

void Octree::InsertPoint(Point *pPoint)
{
    assert(pPoint);
    Node* pNode = NodeContainingPoint(pPoint->m_vOrigin);
    if (pNode) {
        assert(pNode->Type() == kLeaf);
        Leaf* pLeaf = static_cast<Leaf*>(pNode);
        pLeaf->InsertPoint(pPoint);
        if (pLeaf->Size() > m_iMaxCapacity) {
            Split(pLeaf);
        }
    }
    m_bUpdateSize = true;
}

void Octree::RemovePoint(Point *pPoint)
{
    Leaf* pLeaf = pPoint->OctreeLeaf();
    if (!pLeaf) {
        return;
    }
    assert(pLeaf->Type() == kLeaf);
    pLeaf->RemovePoint(pPoint);
    Branch* pBranch = static_cast<Branch*>(pLeaf->Parent());
    assert(pBranch);
    if (pBranch->Size() <= m_iMaxCapacity) {
        Merge(pBranch);
    }
    m_bUpdateSize = true;
}

void Octree::UpdatePoint(Point* pPoint)
{
    Leaf* pLeaf = pPoint->OctreeLeaf();
    if (pLeaf) {
        if (pPoint->Active()) {
            RemovePoint(pPoint);
        } else {
            if (!pLeaf->Box().Contains(pPoint->m_vOrigin)) {
                RemovePoint(pPoint);
                InsertPoint(pPoint);
            }
        }
    } else {
        if (!pPoint->Active()) {
            InsertPoint(pPoint);
        }
    }
}

Octree::Node* Octree::NodeContainingPoint(const O5Vec3& vPoint)
{
    return m_pRootNode->NodeContainingPoint(vPoint);
}


void Octree::PointsInBox(const Box& sBox, std::vector<Point*>& rPointsVector) const
{
    m_pRootNode->PointsInBox(sBox, rPointsVector);
}

unsigned long Octree::Size()
{
    if (m_bUpdateSize) {
        m_iSize = m_pRootNode->Size();
        m_bUpdateSize = false;
    }
    return m_iSize;
}


//--------------------------------------------------------------------------------------------------
// Node
//--------------------------------------------------------------------------------------------------

#pragma mark Node

Octree::Node::Node(Factory::Box sBox)
    :m_sBox(sBox)
    ,m_pParent(NULL)
    ,m_eType(kLeaf)
    ,m_iDepth(0)
{
    
}

void Octree::Node::Render() const
{
    if (Type() == kLeaf) {
        static_cast<const Leaf*>(this)->Render();
    } else {
        static_cast<const Branch*>(this)->Render();
    }
}

Octree::Node* Octree::Node::NodeContainingPoint(const O5Vec3& vPoint)
{
    if (m_sBox.Contains(vPoint)) {
        if (Type() == kBranch) {
            const Branch* pBranch = static_cast<const Branch*>(this);
            for(int x = 0; x < 2; x++) {
                for(int y = 0; y < 2; y++) {
                    for(int z = 0; z < 2; z++) {
                        Node* pChild = pBranch->Child(x, y, z);
                        if (pChild->m_sBox.Contains(vPoint)) {
                            return pChild->NodeContainingPoint(vPoint);
                        }
                    }
                }
            }
        } else {
            return this;
        }
    }
    return NULL;
}

void Octree::Node::PointsInBox(const struct Box& sBox, std::vector<Point*>& rPointsVector) const
{
    if (m_sBox.Intersects(sBox)) {
        if (Type() == kBranch) {
            const Branch* pBranch = static_cast<const Branch*>(this);
            for(int x = 0; x < 2; x++) {
                for(int y = 0; y < 2; y++) {
                    for(int z = 0; z < 2; z++) {
                        Node* pChild = pBranch->Child(x, y, z);
                        if (pChild->m_sBox.Intersects(sBox)) {
                            pChild->PointsInBox(sBox, rPointsVector);
                        }
                    }
                }
            }
        } else {
            const Leaf* pLeaf = static_cast<const Leaf*>(this);
            const TPointsList& rPointsList = pLeaf->Points();
            for(auto i = rPointsList.begin(); i != rPointsList.end(); ++i) {
                rPointsVector.push_back(*i);
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------
// Branch
//--------------------------------------------------------------------------------------------------


#pragma mark Branch

Octree::Branch::Branch(struct Box sBox) : Node(sBox)
{
    m_eType = kBranch;
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                m_pChildrenArray[x][y][z] = NULL;
            }
        }
    }
}

Octree::Branch::~Branch()
{
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                FT_DELETE(m_pChildrenArray[x][y][z]);
            }
        }
    }
}


void Octree::Branch::Render() const
{
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                Child(x, y, z)->Render();
            }
        }
    }
}

void Octree::Branch::SetChild(SIndex& sIndex, Node* pNode)
{
    SetChild(sIndex.m_iX, sIndex.m_iY, sIndex.m_iZ, pNode);
}

void Octree::Branch::SetChild(int x, int y, int z, Node* pNode)
{
    m_pChildrenArray[x][y][z] = pNode;
    pNode->SetIndex(SIndex(x, y, z));
    pNode->SetParent(this);
    pNode->SetDepth(m_iDepth+1);
}

unsigned long Octree::Branch::Size() const
{
    unsigned long iSize = 0;
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                iSize += Child(x, y, z)->Size();
            }
        }
    }
    return iSize;
}


//--------------------------------------------------------------------------------------------------
// Leaf
//--------------------------------------------------------------------------------------------------

#pragma mark Leaf

void Octree::Leaf::Render() const
{
    const Vec3 vertices[]= {
        // 0
        m_sBox.m_vCenter.m_fX - m_sBox.m_vHalfDimention.m_fX,
        m_sBox.m_vCenter.m_fY - m_sBox.m_vHalfDimention.m_fY,
        m_sBox.m_vCenter.m_fZ + m_sBox.m_vHalfDimention.m_fZ,
        // 1
        m_sBox.m_vCenter.m_fX - m_sBox.m_vHalfDimention.m_fX,
        m_sBox.m_vCenter.m_fY + m_sBox.m_vHalfDimention.m_fY,
        m_sBox.m_vCenter.m_fZ + m_sBox.m_vHalfDimention.m_fZ,
        // 2
        m_sBox.m_vCenter.m_fX + m_sBox.m_vHalfDimention.m_fX,
        m_sBox.m_vCenter.m_fY + m_sBox.m_vHalfDimention.m_fY,
        m_sBox.m_vCenter.m_fZ + m_sBox.m_vHalfDimention.m_fZ,
        // 3
        m_sBox.m_vCenter.m_fX + m_sBox.m_vHalfDimention.m_fX,
        m_sBox.m_vCenter.m_fY - m_sBox.m_vHalfDimention.m_fY,
        m_sBox.m_vCenter.m_fZ + m_sBox.m_vHalfDimention.m_fZ,
        // 4
        m_sBox.m_vCenter.m_fX - m_sBox.m_vHalfDimention.m_fX,
        m_sBox.m_vCenter.m_fY - m_sBox.m_vHalfDimention.m_fY,
        m_sBox.m_vCenter.m_fZ - m_sBox.m_vHalfDimention.m_fZ,
        // 5
        m_sBox.m_vCenter.m_fX - m_sBox.m_vHalfDimention.m_fX,
        m_sBox.m_vCenter.m_fY + m_sBox.m_vHalfDimention.m_fY,
        m_sBox.m_vCenter.m_fZ - m_sBox.m_vHalfDimention.m_fZ,
        // 6
        m_sBox.m_vCenter.m_fX + m_sBox.m_vHalfDimention.m_fX,
        m_sBox.m_vCenter.m_fY + m_sBox.m_vHalfDimention.m_fY,
        m_sBox.m_vCenter.m_fZ - m_sBox.m_vHalfDimention.m_fZ,
        // 7
        m_sBox.m_vCenter.m_fX + m_sBox.m_vHalfDimention.m_fX,
        m_sBox.m_vCenter.m_fY - m_sBox.m_vHalfDimention.m_fY,
        m_sBox.m_vCenter.m_fZ - m_sBox.m_vHalfDimention.m_fZ,
    };
    
    static const GLubyte indices[] = {
        0, 1,   1, 2,   2, 3,   3, 0,
        4, 5,   5, 6,   6, 7,   7, 4,
        0, 4,   1, 5,   2, 6,   3, 7
    };

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glLineWidth(1);
    glColor4f(0.0f, 1.0f, 0.0f, 0.3f);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, indices);
    GetError();
    glDisableClientState(GL_VERTEX_ARRAY);
}


void Octree::Leaf::InsertPoint(Point* pPoint)
{
    m_cPointsList.push_back(pPoint);
    pPoint->SetOctreeLeaf(this);
}

void Octree::Leaf::RemovePoint(Point* pPoint)
{
    m_cPointsList.remove(pPoint);
    pPoint->SetOctreeLeaf(NULL);
}

}




