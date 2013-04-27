
#include <Model/ModelTreeManager.h>
#include <Model/PointNode.h>

namespace ftr {

ModelTreeManager::ModelTreeManager()
{
    mOctree = new ftr::Octree(Box(Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 20.0f, 20.0f)));
}

ModelTreeManager::~ModelTreeManager()
{
    FT_DELETE(mOctree);
}

#pragma mark Instance

void ModelTreeManager::setRootNode(Node *pRootNode)
{
    mRootNode = pRootNode;
}

void ModelTreeManager::AddNode(Node* pNode)
{
    if (pNode->Type() == Node::kPoint) {
        mOctree->InsertPoint(static_cast<PointNode*>(pNode));
    }
}

void ModelTreeManager::UpdateNode(Node* pNode)
{
    if (pNode->Type() == Node::kPoint) {
        mOctree->UpdatePoint(static_cast<PointNode*>(pNode));
    }
}

void ModelTreeManager::RemoveNode(Node* pNode)
{
    if (pNode->Type() == Node::kPoint) {
        mOctree->RemovePoint(static_cast<PointNode*>(pNode));
    }
    Node* supernode = pNode->Supernode();
    assert(supernode);
    supernode->RemoveNode(pNode);
}

}
