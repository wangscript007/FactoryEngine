
#pragma once

class RectangleInteraction;
class LineInteraction;
class MoveInteraction;
class RotationInteraction;
class ScaleInteraction;
class ModelManager;

namespace Factory {

class InteractionManager
{
public:
    InteractionManager(ModelManager& rModelManager);
    virtual ~InteractionManager();
    
    RectangleInteraction* RectangleInteraction() const { return m_pRectangleInteraction; }
    LineInteraction* LineInteraction() const { return m_pLineInteraction; }
    MoveInteraction* MoveInteraction() const { return m_pMoveInteraction; }
    RotationInteraction* RotationInteraction() const { return m_pRotationInteraction; }
    ScaleInteraction* ScaleInteraction() const { return m_pScaleInteraction; }
    
private:
    RectangleInteraction* m_pRectangleInteraction;
    LineInteraction* m_pLineInteraction;
    MoveInteraction* m_pMoveInteraction;
    RotationInteraction* m_pRotationInteraction;
    ScaleInteraction* m_pScaleInteraction;
    ModelManager& m_rModelManager;
};

}