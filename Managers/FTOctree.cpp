
#include "FTOctree.h"
#include "FTGLError.h"


FTOctree::FTOctree(FTBox sBox)
    :m_iMaxCapacity(2)
    ,m_iMaxDepth(9)
{
    m_pRootNode = Split(new Leaf(sBox));
}

FTOctree::~FTOctree()
{
}

#pragma mark Instance



void FTOctree::Render()
{
    reinterpret_cast<Node*>(m_pRootNode)->Render();
}

FTOctree::Branch* FTOctree::Split(FTOctree::Leaf *pLeaf)
{
    Branch* pBranch =  new Branch(pLeaf->Box());
    Leaf* leaf;
    FTBox sBox = pLeaf->Box();
    O5Vec3 vHalf = O5Vec3(sBox.m_vHalfDimention.m_fX/2.0f,
                          sBox.m_vHalfDimention.m_fY/2.0f,
                          sBox.m_vHalfDimention.m_fZ/2.0f);
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                //
                // Create leaf and add intersecting points
                //
                O5Vec3 vCenter;
                if (x == 0) {
                    vCenter.m_fX = sBox.m_vCenter.m_fX - vHalf.m_fX;
                } else {
                    vCenter.m_fX = sBox.m_vCenter.m_fX + vHalf.m_fX;
                }
                if (y == 0) {
                    vCenter.m_fY = sBox.m_vCenter.m_fY + vHalf.m_fY;
                } else {
                    vCenter.m_fY = sBox.m_vCenter.m_fY - vHalf.m_fY;
                }
                if (z == 0) {
                    vCenter.m_fZ = sBox.m_vCenter.m_fZ + vHalf.m_fZ;
                } else {
                    vCenter.m_fZ = sBox.m_vCenter.m_fZ - vHalf.m_fZ;
                }
                leaf = new Leaf(FTBox(vCenter, vHalf));
                pBranch->SetChild(x, y, z, leaf);
            }
        }
    }
    if (pLeaf->Parent()) {
        reinterpret_cast<Branch*>(pLeaf->Parent())->SetChild(pLeaf->Index(), pBranch);
        pBranch->SetParent(pLeaf->Parent());
    }
    delete pLeaf;
    return pBranch;
}

void FTOctree::Merge(Branch* pBrach)
{
    
}

void FTOctree::InsertPoint(FTPoint *pPoint)
{
    
}

void FTOctree::RemovePoint(FTPoint *pPoint)
{
    
}

#pragma mark Node

FTOctree::Node::Node(FTBox sBox)
    :m_sBox(sBox)
    ,m_pParent(NULL)
{
    
}

void FTOctree::Node::Render()
{
    if (Type() == kLeaf) {
        reinterpret_cast<Leaf*>(this)->Render();
    } else {
        reinterpret_cast<Branch*>(this)->Render();
    }
}



#pragma mark Branch

FTOctree::Branch::Branch(FTBox sBox) : Node(sBox)
{
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                m_pChildrenArray[x][y][z] = NULL;
            }
        }
    }
}


void FTOctree::Branch::Render()
{
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                Child(x, y, z)->Render();
            }
        }
    }
}

void FTOctree::Branch::SetChild(SIndex& sIndex, Node* pNode)
{
    SetChild(sIndex.m_iX, sIndex.m_iY, sIndex.m_iZ, pNode);
}

void FTOctree::Branch::SetChild(int x, int y, int z, Node* pNode)
{
    m_pChildrenArray[x][y][z] = pNode;
    pNode->SetIndex(SIndex(x, y, z));
    pNode->SetParent(this);
}

#pragma mark Leaf

void FTOctree::Leaf::Render()
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


void FTOctree::Leaf::InsertPoint(FTPoint* pPoint)
{
    m_cPointsList.push_back(pPoint);
}

void FTOctree::Leaf::RemovePoint(FTPoint* pPoint)
{
    m_cPointsList.remove(pPoint);
}





