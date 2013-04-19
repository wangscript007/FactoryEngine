
#include <Managers/ModelTreeManager.h>
#include <Model/Point.h>

namespace ftr {

ModelTreeManager::ModelTreeManager()
{
    mOctree = new ftr::Octree(Box(Vec3(0.0f, 0.0f, 0.0f), Vec3(8.0f, 8.0f, 8.0f)));
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
        mOctree->InsertPoint(static_cast<Point*>(pNode));
    }
}

void ModelTreeManager::UpdateNode(Node* pNode)
{
    if (pNode->Type() == Node::kPoint) {
        mOctree->UpdatePoint(static_cast<Point*>(pNode));
    }
}

void ModelTreeManager::RemoveNode(Node* pNode)
{
    if (pNode->Type() == Node::kPoint) {
        mOctree->RemovePoint(static_cast<Point*>(pNode));
    }
    Node* supernode = pNode->Supernode();
    assert(supernode);
    supernode->RemoveNode(pNode);
}

}
