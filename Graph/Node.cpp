
#include <Graph/PointNode.h>
#include <Graph/Node.h>
#include <Utils/Description.h>
#include <Processing/ColorPickingMapper.h>

namespace ftr {
    
Node::Node() :
    mSupernode(NULL),
    mPickingId(-1)
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
}
    
void Node::Invalidate()
{
    for(auto &node : mSubnodes)
    {
        node->Invalidate();
    }
}

void Node::Transform(const glm::mat4& m4Transformation)
{    
    for(auto &node : mSubnodes)
    {
        node->Transform(m4Transformation);
    }
}
    
void Node::setPickingId(int pickingId)
{
    mPickingId = pickingId;
    for(auto &node : mSubnodes) {
        node->setPickingId(pickingId);
    }
    std::cout << Description::Described(ColorPickingMapper::ColorFromInt(mPickingId)) << std::endl;
    Invalidate();
}
    
void Node::setSelected(bool selected)
{
    mSelected = selected;
    Invalidate();
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
    
glm::vec3 Node::Center() const
{
    glm::vec3 sum;
    for (auto &node : mSubnodes) {
        sum += node->Center();
    }
    return sum/static_cast<float>(mSubnodes.size());
}

}