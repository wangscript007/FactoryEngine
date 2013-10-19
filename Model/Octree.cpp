
#include <Model/Octree.h>
#include <Model/PointNode.h>
#include <Main/GLError.h>


namespace ftr {

Octree::Octree(Box sBox)
    :mMaxCapacity(2)
    ,mMaxDepth(9)
    ,mSize(0)
    ,mUpdateSize(true)

{
    mRootNode = Split(new Leaf(sBox));
}

Octree::~Octree()
{
    FT_DELETE(mRootNode);
}

#pragma mark Instance

void Octree::Render()
{
    return;
    static_cast<Node*>(mRootNode)->Render();
}


Octree::Branch* Octree::Split(Octree::Leaf *leaf)
{
    if (leaf->Depth() >= mMaxDepth) {
        return NULL;
    }
    unsigned long iInitialCount = leaf->Size();
    unsigned long iCounter = 0;
    TPointsList cPointsList = leaf->PointNodes();
    Branch* branch =  new Branch(leaf->Box());
    if (leaf->Parent()) {
        assert(leaf->Parent()->Type() == kBranch);
        static_cast<Branch*>(leaf->Parent())->setChild(leaf->Index(), branch);
    }
    Leaf* childLeaf;
    Box sBox = leaf->Box();
    glm::vec3 half = sBox.mHalfDimention/2.0f;
    glm::vec3 center;
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                if (x == 0) {
                    center.x = sBox.mCenter.x - half.x;
                } else {
                    center.x = sBox.mCenter.x + half.x;
                }
                if (y == 0) {
                    center.y = sBox.mCenter.y - half.y;
                } else {
                    center.y = sBox.mCenter.y + half.y;
                }
                if (z == 0) {
                    center.z = sBox.mCenter.z - half.z;
                } else {
                    center.z = sBox.mCenter.z + half.z;
                }
                childLeaf = new Leaf(Box(center, half));
                for(auto i = cPointsList.begin(); i != cPointsList.end(); ++i) {
                    if (childLeaf->Box().Contains((*i)->mOrigin)) {
                        childLeaf->InsertPoint(*i);
                        iCounter++;
                    }
                }
                branch->setChild(x, y, z, childLeaf);
                if (childLeaf->Size() > mMaxCapacity) {
                    Split(childLeaf);
                }
            }
        }
    }
    assert(iCounter == iInitialCount);
    FT_DELETE(leaf);
    mUpdateSize = true;
    return branch;
}

void Octree::Merge(Branch* branch)
{
    if (branch == mRootNode) {
        return;
    }
    assert(branch->Type() == kBranch);
    Leaf* leaf = new Leaf(branch->Box());
    if (branch->Parent()) {
        assert(branch->Parent()->Type() == kBranch);
        static_cast<Branch*>(branch->Parent())->setChild(branch->Index(), leaf);
    }
    TPointsList cPointsList;
    Leaf* childLeaf;
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                childLeaf = static_cast<Leaf*>(branch->Child(x, y, z));
                cPointsList = childLeaf->PointNodes();
                for(auto i = cPointsList.begin(); i != cPointsList.end(); ++i) {
                    leaf->InsertPoint((*i));
                }
            }
        }
    }
    Branch* pParent = static_cast<Branch*>(branch->Parent());
    if (pParent) {
        if (pParent->Size() <= mMaxCapacity) {
            Merge(pParent);
        }
    }
    FT_DELETE(branch);
}

void Octree::InsertPoint(PointNode *pPoint)
{
    assert(pPoint);
    Node* pNode = NodeContainingPoint(pPoint->mOrigin);
    if (pNode) {
        assert(pNode->Type() == kLeaf);
        Leaf* leaf = static_cast<Leaf*>(pNode);
        leaf->InsertPoint(pPoint);
        if (leaf->Size() > mMaxCapacity) {
            Split(leaf);
        }
    }
    mUpdateSize = true;
}

void Octree::RemovePoint(PointNode *pPoint)
{
    Leaf* leaf = pPoint->OctreeLeaf();
    if (!leaf) {
        return;
    }
    assert(leaf->Type() == kLeaf);
    leaf->RemovePoint(pPoint);
    Branch* branch = static_cast<Branch*>(leaf->Parent());
    assert(branch);
    if (branch->Size() <= mMaxCapacity) {
        Merge(branch);
    }
    mUpdateSize = true;
}

void Octree::UpdatePoint(PointNode* pPoint)
{
    Leaf* leaf = pPoint->OctreeLeaf();
    if (leaf) {
        if (pPoint->Active()) {
            RemovePoint(pPoint);
        } else {
            if (!leaf->Box().Contains(pPoint->mOrigin)) {
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

Octree::Node* Octree::NodeContainingPoint(const glm::vec3& point)
{
    return mRootNode->NodeContainingPoint(point);
}


void Octree::PointNodesInBox(const Box& sBox, std::vector<PointNode*>& pointsVector) const
{
    mRootNode->PointNodesInBox(sBox, pointsVector);
}

void Octree::PointNodesInCylinder(const Cylinder& cylinder, std::vector<PointNode*>& pointsVector) const
{
    mRootNode->PointNodesInCylinder(cylinder, pointsVector);
}

unsigned long Octree::Size()
{
    if (mUpdateSize) {
        mSize = mRootNode->Size();
        mUpdateSize = false;
    }
    return mSize;
}


//--------------------------------------------------------------------------------------------------
// Node
//--------------------------------------------------------------------------------------------------

#pragma mark Node

Octree::Node::Node(ftr::Box sBox)
    :mBox(sBox)
    ,mParent(NULL)
    ,m_eType(kLeaf)
    ,mDepth(0)
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

Octree::Node* Octree::Node::NodeContainingPoint(const glm::vec3& point)
{
    if (mBox.Contains(point)) {
        if (Type() == kBranch) {
            const Branch* branch = static_cast<const Branch*>(this);
            for(int x = 0; x < 2; x++) {
                for(int y = 0; y < 2; y++) {
                    for(int z = 0; z < 2; z++) {
                        Node* child = branch->Child(x, y, z);
                        if (child->mBox.Contains(point)) {
                            return child->NodeContainingPoint(point);
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

void Octree::Node::PointNodesInBox(const struct Box& sBox, std::vector<PointNode*>& pointsVector) const
{
    if (mBox.Intersects(sBox)) {
        if (Type() == kBranch) {
            const Branch* branch = static_cast<const Branch*>(this);
            for(int x = 0; x < 2; x++) {
                for(int y = 0; y < 2; y++) {
                    for(int z = 0; z < 2; z++) {
                        Node* child = branch->Child(x, y, z);
                        if (child->mBox.Intersects(sBox)) {
                            child->PointNodesInBox(sBox, pointsVector);
                        }
                    }
                }
            }
        } else {
            const Leaf* leaf = static_cast<const Leaf*>(this);
            const TPointsList& pointsList = leaf->PointNodes();
            for(auto i = pointsList.begin(); i != pointsList.end(); ++i) {
                pointsVector.push_back(*i);
            }
        }
    }
}
    
void Octree::Node::PointNodesInCylinder(const Cylinder& cylinder, std::vector<PointNode*>& pointsVector) const
{
    if (cylinder.Intersects(mBox)) {
        if (Type() == kBranch) {
            const Branch* branch = static_cast<const Branch*>(this);
            for(int x = 0; x < 2; x++) {
                for(int y = 0; y < 2; y++) {
                    for(int z = 0; z < 2; z++) {
                        Node* child = branch->Child(x, y, z);
                        if (cylinder.Intersects(child->mBox)) {
                            child->PointNodesInCylinder(cylinder, pointsVector);
                        }
                    }
                }
            }
        } else {
            const Leaf* leaf = static_cast<const Leaf*>(this);
            const TPointsList& pointsList = leaf->PointNodes();
            for(auto i = pointsList.begin(); i != pointsList.end(); ++i) {
                pointsVector.push_back(*i);
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
                mChildrenArray[x][y][z] = NULL;
            }
        }
    }
}

Octree::Branch::~Branch()
{
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                FT_DELETE(mChildrenArray[x][y][z]);
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

void Octree::Branch::setChild(SIndex& sIndex, Node* pNode)
{
    setChild(sIndex.x, sIndex.y, sIndex.z, pNode);
}

void Octree::Branch::setChild(int x, int y, int z, Node* pNode)
{
    mChildrenArray[x][y][z] = pNode;
    pNode->setIndex(SIndex(x, y, z));
    pNode->setParent(this);
    pNode->setDepth(mDepth+1);
}

unsigned long Octree::Branch::Size() const
{
    unsigned long size = 0;
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            for(int z = 0; z < 2; z++) {
                size += Child(x, y, z)->Size();
            }
        }
    }
    return size;
}


//--------------------------------------------------------------------------------------------------
// Leaf
//--------------------------------------------------------------------------------------------------

#pragma mark Leaf

void Octree::Leaf::Render() const
{
    const Vertice3 vertices[]= {
        // 0
        mBox.mCenter.x - mBox.mHalfDimention.x,
        mBox.mCenter.y - mBox.mHalfDimention.y,
        mBox.mCenter.z + mBox.mHalfDimention.z,
        // 1
        mBox.mCenter.x - mBox.mHalfDimention.x,
        mBox.mCenter.y + mBox.mHalfDimention.y,
        mBox.mCenter.z + mBox.mHalfDimention.z,
        // 2
        mBox.mCenter.x + mBox.mHalfDimention.x,
        mBox.mCenter.y + mBox.mHalfDimention.y,
        mBox.mCenter.z + mBox.mHalfDimention.z,
        // 3
        mBox.mCenter.x + mBox.mHalfDimention.x,
        mBox.mCenter.y - mBox.mHalfDimention.y,
        mBox.mCenter.z + mBox.mHalfDimention.z,
        // 4
        mBox.mCenter.x - mBox.mHalfDimention.x,
        mBox.mCenter.y - mBox.mHalfDimention.y,
        mBox.mCenter.z - mBox.mHalfDimention.z,
        // 5
        mBox.mCenter.x - mBox.mHalfDimention.x,
        mBox.mCenter.y + mBox.mHalfDimention.y,
        mBox.mCenter.z - mBox.mHalfDimention.z,
        // 6
        mBox.mCenter.x + mBox.mHalfDimention.x,
        mBox.mCenter.y + mBox.mHalfDimention.y,
        mBox.mCenter.z - mBox.mHalfDimention.z,
        // 7
        mBox.mCenter.x + mBox.mHalfDimention.x,
        mBox.mCenter.y - mBox.mHalfDimention.y,
        mBox.mCenter.z - mBox.mHalfDimention.z,
    };
    
    static const GLubyte indices[] = {
        0, 1,   1, 2,   2, 3,   3, 0,
        4, 5,   5, 6,   6, 7,   7, 4,
        0, 4,   1, 5,   2, 6,   3, 7
    };
    
}


void Octree::Leaf::InsertPoint(PointNode* pPoint)
{
    mPointsList.push_back(pPoint);
    pPoint->setOctreeLeaf(this);
}

void Octree::Leaf::RemovePoint(PointNode* pPoint)
{
    mPointsList.remove(pPoint);
    pPoint->setOctreeLeaf(NULL);
}

}




