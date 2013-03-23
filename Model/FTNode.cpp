
#include <Model/FTPoint.h>
#include <Model/FTNode.h>

FTNode::FTNode()
{

}

FTNode::~FTNode()
{
    for(auto i = m_pSubnodes.begin(); i != m_pSubnodes.end(); ++i) {
        FT_DELETE(*i);
    }
}

void FTNode::AddNode(FTNode* pNode)
{
    m_pSubnodes.push_back(pNode);
    pNode->m_pSupernode = this;
}

void FTNode::RemoveNode(FTNode* pNode)
{
    auto i = std::find(m_pSubnodes.begin(), m_pSubnodes.end(), pNode);
    if (i != m_pSubnodes.end()) {
        m_pSubnodes.erase(i);
    }
}

void FTNode::Render()
{
    for(auto i = m_pSubnodes.begin(); i != m_pSubnodes.end(); ++i)
    {
        (*i)->Render();
    }
}

void FTNode::Transform(const O5Mat4& m4Transformation)
{    
    for(auto i = m_pSubnodes.begin(); i != m_pSubnodes.end(); ++i)
    {
        (*i)->Transform(m4Transformation);
    }
}