
#include <Managers/InteractionManager.h>
#include <Managers/ModelManager.h>
#include <Interaction/RectangleInteraction.h>
#include <Interaction/LineInteraction.h>
#include <Interaction/MoveInteraction.h>
#include <Interaction/RotationInteraction.h>
#include <Interaction/ScaleInteraction.h>

namespace ftr {

InteractionManager::InteractionManager(ModelManager& rModelManager)
    :m_rModelManager(rModelManager)
{
    m_pRectangleInteraction = new class RectangleInteraction(m_rModelManager);
    m_pLineInteraction = new class LineInteraction(m_rModelManager);
    m_pMoveInteraction = new class MoveInteraction(m_rModelManager);
    m_pRotationInteraction = new class RotationInteraction(m_rModelManager);
    m_pScaleInteraction = new class ScaleInteraction(m_rModelManager);
}

InteractionManager::~InteractionManager()
{
    FT_DELETE(m_pRectangleInteraction);
    FT_DELETE(m_pLineInteraction);
    FT_DELETE(m_pMoveInteraction);
    FT_DELETE(m_pRotationInteraction);
    FT_DELETE(m_pScaleInteraction);
}

}