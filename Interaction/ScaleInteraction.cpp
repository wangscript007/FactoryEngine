
#include <Interaction/ScaleInteraction.h>
#include <Managers/ModelManager.h>
#include <Math/Transformation.h>

namespace ftr {


ScaleInteraction::ScaleInteraction(ModelManager& rModelManager)
:m_rModelManager(rModelManager)
,m_bActive(false)
{}

void ScaleInteraction::Render()
{
    
}

#pragma mark Instance

void ScaleInteraction::SetStart(Vec3 vStart)
{
    m_vStart = vStart;
}

void ScaleInteraction::SetEnd(Vec3 vEnd)
{
    m_vEnd = vEnd;
    assert(m_rModelManager.SelectedNode()->Type() == Node::kLine);
    Vec3 vScale = m_vEnd - m_vStart;
    vScale.m_fX = std::min(std::max(vScale.m_fX, 1.0f), 2.0f);
    vScale.m_fY = std::min(std::max(vScale.m_fY, 1.0f), 2.0f);
    vScale.m_fZ = std::min(std::max(vScale.m_fZ, 1.0f), 2.0f);
    vScale.Set(0.99f, 1.001f, 1.001f);
    m_rModelManager.SelectedNode()->Transform(Transformation::Scale(vScale));
    m_vStart = vEnd;
}
    
}

