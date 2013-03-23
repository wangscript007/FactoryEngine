
#include <Interaction/FTRotationInteraction.h>
#include <Managers/FTModelManager.h>
#include <Math/FTTransformation.h>


FTRotationInteraction::FTRotationInteraction(FTModelManager& rModelManager)
:m_rModelManager(rModelManager)
,m_bActive(false)
{}

void FTRotationInteraction::Render()
{
    
}

#pragma mark Instance

void FTRotationInteraction::SetStart(O5Vec3 vStart)
{
    m_vStart = vStart;
}

void FTRotationInteraction::SetEnd(O5Vec3 vEnd)
{
    m_vEnd = vEnd;
    assert(m_rModelManager.SelectedNode()->Type() == FTNode::kLine);
    m_rModelManager.SelectedNode()->Transform(FTTransformation::Rotate(m_vEnd - m_vStart));
    m_vStart = vEnd;
}

