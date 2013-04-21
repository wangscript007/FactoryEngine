
#include <Model/PointNode.h>
#include <Model/Node.h>

namespace ftr {
    
Node::Node()
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

void Node::Render(RenderBundle& renderBundle)
{
    for(auto i = mSubnodes.begin(); i != mSubnodes.end(); ++i)
    {
        (*i)->Render(renderBundle);
    }
}

void Node::Transform(const Mat4& m4Transformation)
{    
    for(auto i = mSubnodes.begin(); i != mSubnodes.end(); ++i)
    {
        (*i)->Transform(m4Transformation);
    }
}

}