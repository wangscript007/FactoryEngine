
#include <Interaction/MoveInteraction.h>
#include <Managers/ModelManager.h>
#include <Math/Transformation.h>

namespace Factory {

MoveInteraction::MoveInteraction(ModelManager& rModelManager)
:m_rModelManager(rModelManager)
,m_bActive(false)
{}

void MoveInteraction::Render()
{
    
}

#pragma mark Instance

void MoveInteraction::SetStart(Vec3 vStart)
{
    m_vStart = vStart;
}

void MoveInteraction::SetEnd(Vec3 vEnd)
{
    m_vEnd = vEnd;
    assert(m_rModelManager.SelectedNode()->Type() == Node::kLine);
    m_rModelManager.SelectedNode()->Transform(Transformation::Move(m_vEnd - m_vStart));
    m_vStart = vEnd;
}

}
