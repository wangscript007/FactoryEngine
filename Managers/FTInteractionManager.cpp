
#include <Managers/FTInteractionManager.h>
#include <Managers/FTModelManager.h>
#include <Interaction/FTRectangleInteraction.h>

FTInteractionManager::FTInteractionManager(FTModelManager& rModelManager)
    :m_rModelManager(rModelManager)
{
    m_pRectangleInteraction = new FTRectangleInteraction(m_rModelManager);
}

FTInteractionManager::~FTInteractionManager()
{
    FT_DELETE(m_pRectangleInteraction);
}