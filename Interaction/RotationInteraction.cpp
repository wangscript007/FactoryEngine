
#include <Interaction/RotationInteraction.h>
#include <Managers/ModelManager.h>
#include <Math/Transformation.h>

namespace Factory {

RotationInteraction::RotationInteraction(ModelManager& rModelManager)
:m_rModelManager(rModelManager)
,m_bActive(false)
{}

void RotationInteraction::Render()
{
    
}

#pragma mark Instance

void RotationInteraction::SetStart(O5Vec3 vStart)
{
    m_vStart = vStart;
}

void RotationInteraction::SetEnd(O5Vec3 vEnd)
{
    m_vEnd = vEnd;
    assert(m_rModelManager.SelectedNode()->Type() == Node::kLine);
    m_rModelManager.SelectedNode()->Transform(Transformation::Rotate(m_vEnd - m_vStart));
    m_vStart = vEnd;
}

}