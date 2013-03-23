
#include <Managers/FTInteractionManager.h>
#include <Managers/FTModelManager.h>
#include <Interaction/FTRectangleInteraction.h>
#include <Interaction/FTLineInteraction.h>
#include <Interaction/FTMoveInteraction.h>

FTInteractionManager::FTInteractionManager(FTModelManager& rModelManager)
    :m_rModelManager(rModelManager)
{
    m_pRectangleInteraction = new FTRectangleInteraction(m_rModelManager);
    m_pLineInteraction = new FTLineInteraction(m_rModelManager);
    m_pMoveInteraction = new FTMoveInteraction(m_rModelManager);
}

FTInteractionManager::~FTInteractionManager()
{
    FT_DELETE(m_pRectangleInteraction);
    FT_DELETE(m_pLineInteraction);
    FT_DELETE(m_pMoveInteraction);
}