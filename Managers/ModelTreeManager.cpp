
#include <Managers/ModelTreeManager.h>
#include <Model/Point.h>

namespace Factory {

ModelTreeManager::ModelTreeManager()
{
    m_pOctree = new Octree(Box(O5Vec3(0.0f, 0.0f, 0.0f), O5Vec3(8.0f, 8.0f, 8.0f)));
}

ModelTreeManager::~ModelTreeManager()
{
    FT_DELETE(m_pOctree);
}

#pragma mark Instance

void ModelTreeManager::SetRootNode(Node *pRootNode)
{
    m_pRootNode = pRootNode;
}

void ModelTreeManager::AddNode(Node* pNode)
{
    if (pNode->Type() == Node::kPoint) {
        m_pOctree->InsertPoint(static_cast<Point*>(pNode));
    }
}

void ModelTreeManager::UpdateNode(Node* pNode)
{
    if (pNode->Type() == Node::kPoint) {
        m_pOctree->UpdatePoint(static_cast<Point*>(pNode));
    }
}

void ModelTreeManager::RemoveNode(Node* pNode)
{
    if (pNode->Type() == Node::kPoint) {
        m_pOctree->RemovePoint(static_cast<Point*>(pNode));
    }
    Node* pSupernode = pNode->Supernode();
    assert(pSupernode);
    pSupernode->RemoveNode(pNode);
}

}
