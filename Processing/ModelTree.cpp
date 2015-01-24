


#include <Processing/ModelTree.h>
#include <Graph/PointNode.h>
#include <Graph/GroupNode.h>

namespace ftr {

ModelTree::ModelTree()
{
    mOctree = new ftr::Octree(Box(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(500.0f, 500, 500.0f)));
}

ModelTree::~ModelTree()
{
    FT_DELETE(mOctree);
}

#pragma mark Instance
    
void ModelTree::Render(Layer& layer)
{
    for (int i = 0; i < mGroups.size(); ++i) {
        mGroups[i]->Render(layer);
    }
}
    
void ModelTree::AddGroup(GroupNode* groupNode)
{
    mGroups.push_back(groupNode);
}

void ModelTree::AddNode(Node* pNode)
{
    
    if (pNode->Type() == Node::kPoint) {
        mOctree->InsertPoint(static_cast<PointNode*>(pNode));
    }
}

void ModelTree::UpdateNode(Node* node)
{
    std::vector<Node*> pointNodes;
    std::vector<PointNode*> pointNodesToInsert;
    node->PointNodes(pointNodes);
    for (auto &pointNode : pointNodes) {
        PointNode* pointNode2 = static_cast<PointNode*>(pointNode);
        if (pointNode2->OctreeLeafIsInvalid()) {
            mOctree->RemovePoint(pointNode2);
            pointNodesToInsert.push_back(pointNode2);
        }
    }
    for (auto &pointNode : pointNodesToInsert) {
        mOctree->InsertPoint(pointNode);
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
