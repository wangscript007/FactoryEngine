
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
    for(auto i = mSubnodes.begin(); i != mSubnodes.end(); ++i) {
        FT_DELETE(*i);
    }
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
    

}