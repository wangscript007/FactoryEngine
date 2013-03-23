
#include <Interaction/FTMoveInteraction.h>
#include <Managers/FTModelManager.h>
#include <Math/FTTransformation.h>


FTMoveInteraction::FTMoveInteraction(FTModelManager& rModelManager)
:m_rModelManager(rModelManager)
,m_bActive(false)
{}

void FTMoveInteraction::Render()
{
    
}

#pragma mark Instance

void FTMoveInteraction::SetStart(O5Vec3 vStart)
{
    m_vStart = vStart;
}

void FTMoveInteraction::SetEnd(O5Vec3 vEnd)
{
    m_vEnd = vEnd;
    assert(m_rModelManager.SelectedNode()->Type() == FTNode::kLine);
    m_rModelManager.SelectedNode()->Transform(FTTransformation::Move(m_vEnd - m_vStart));
    m_vStart = vEnd;
}

