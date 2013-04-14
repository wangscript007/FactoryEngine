
#include <Model/Point.h>
#include <Model/Node.h>

namespace ftr {
    
Node::Node()
{

}

Node::~Node()
{
    for(auto i = m_pSubnodes.begin(); i != m_pSubnodes.end(); ++i) {
        FT_DELETE(*i);
    }
}

void Node::AddNode(Node* pNode)
{
    m_pSubnodes.push_back(pNode);
    pNode->m_pSupernode = this;
}

void Node::RemoveNode(Node* pNode)
{
    auto i = std::find(m_pSubnodes.begin(), m_pSubnodes.end(), pNode);
    if (i != m_pSubnodes.end()) {
        m_pSubnodes.erase(i);
    }
}

void Node::Render()
{
    for(auto i = m_pSubnodes.begin(); i != m_pSubnodes.end(); ++i)
    {
        (*i)->Render();
    }
}

void Node::Transform(const Mat4& m4Transformation)
{    
    for(auto i = m_pSubnodes.begin(); i != m_pSubnodes.end(); ++i)
    {
        (*i)->Transform(m4Transformation);
    }
}

}