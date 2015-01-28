
#include <Graph/PointNode.h>
#include <Graph/Node.h>
#include <Utils/Description.h>
#include <Processing/ColorPickingMapper.h>

namespace ftr {
    
Node::Node() :
    mSupernode(NULL),
    mInvalid(true),
    mPickingId(-1),
    mSelected(false)
{
}

Node::~Node()
{
    FT_DELETE_VECTOR(mSubnodes)
}

void Node::AddNode(Node* pNode)
{
    mSubnodes.push_back(pNode);
    pNode->mSupernode = this;
}

void Node::RemoveNode(Node* pNode)
{
    auto i = std::find(mSubnodes.begin(), mSubnodes.end(), pNode);
    if (i != mSubnodes.end()) {
        mSubnodes.erase(i);
    }
}

void Node::Render(Layer& layer)
{
    for(auto &node : mSubnodes)
    {
        node->Render(layer);
    }
    mInvalid = false;
    
}
    
void Node::Invalidate(bool recursively)
{
    if (mInvalid) return;

    mInvalid = true;
    if (recursively) {
        for(auto &node : mSubnodes)
        {
            node->Invalidate(recursively);
        }
    }
}

void Node::Transform(const glm::mat4& transformation)
{    
    for(auto &node : mSubnodes)
    {
        node->Transform(transformation);
    }
}
    
void Node::PointNodes(std::vector<Node*>& result) const
{
    for(auto &node : mSubnodes) {
        node->PointNodes(result);
    }
}
    
void Node::setPickingId(int pickingId)
{
    mPickingId = pickingId;
    for(auto &node : mSubnodes) {
        node->setPickingId(pickingId);
    }
//    std::cout << Description::Described(ColorPickingMapper::ColorFromInt(mPickingId)) << std::endl;
    Invalidate(false);
}
    
void Node::setSelected(bool selected)
{
    mSelected = selected;
    Invalidate(false);
}
    
    
void Node::SubnodesWithType(enum Type nodeType, std::vector<Node*>& result) const
{
    for(auto &node : mSubnodes) {
        if (node->Type() == nodeType) {
            result.push_back(node);
        } else {
            node->SubnodesWithType(nodeType, result);
        }
    }
}
    
Node* Node::SubnodeWithCenterNearestToPoint(const glm::vec3& point, enum Type nodeType) const
{
    std::vector<Node*> subnodesWithType;
    SubnodesWithType(nodeType, subnodesWithType);
    float minLenght = INFINITY;
    Node* result = NULL;
    for(auto &node : subnodesWithType) {
        float length = glm::length(point - node->Center());
        if (length < minLenght) {
            result = node;
            minLenght = length;
        }
    }
    return result;
}
    
    
glm::vec3 Node::Center() const
{
    glm::vec3 sum;
    for (auto &node : mSubnodes) {
        sum += node->Center();
    }
    return sum/static_cast<float>(mSubnodes.size());
}
    

char Node::Depth() const
{
    if (mSupernode) {
        return mSupernode->Depth()+1;
    }
    return 0;
}

}