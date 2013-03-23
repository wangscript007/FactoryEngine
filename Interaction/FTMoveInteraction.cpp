
#include <Interaction/FTMoveInteraction.h>
#include <Managers/FTModelManager.h>

FTMoveInteraction::FTMoveInteraction(FTModelManager& rModelManager)
:m_rModelManager(rModelManager)
,m_bActive(false)
{}

void FTMoveInteraction::Render()
{
    
}

#pragma mark Instance

void FTMoveInteraction::SetMotion(O5Vec3 vMotion)
{
    m_vMotion = vMotion;
    
}

