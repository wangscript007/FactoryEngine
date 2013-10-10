
#include <Model/ModelTree.h>
#include <Model/PointNode.h>

namespace ftr {

ModelTree::ModelTree()
{
    mOctree = new ftr::Octree(Box(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f)));
}

ModelTree::~ModelTree()
{
    FT_DELETE(mOctree);
}

#pragma mark Instance

void ModelTree::setRootNode(Node *pRootNode)
{
    mRootNode = pRootNode;
}

void ModelTree::AddNode(Node* pNode)
{
    if (pNode->Type() == Node::kPoint) {
        mOctree->InsertPoint(static_cast<PointNode*>(pNode));
    }
}

void ModelTree::UpdateNode(Node* pNode)
{
    if (pNode->Type() == Node::kPoint) {
        mOctree->UpdatePoint(static_cast<PointNode*>(pNode));
    }
}

void ModelTree::RemoveNode(Node* pNode)
{
    if (pNode->Type() == Node::kPoint) {
        mOctree->RemovePoint(static_cast<PointNode*>(pNode));
    }
    Node* supernode = pNode->Supernode();
    assert(supernode);
    supernode->RemoveNode(pNode);
}

}
