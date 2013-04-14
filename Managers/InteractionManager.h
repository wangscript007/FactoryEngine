
#pragma once

namespace Factory {

class RectangleInteraction;
class LineInteraction;
class MoveInteraction;
class RotationInteraction;
class ScaleInteraction;
class ModelManager;



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
    class RectangleInteraction* m_pRectangleInteraction;
    class LineInteraction* m_pLineInteraction;
    class MoveInteraction* m_pMoveInteraction;
    class RotationInteraction* m_pRotationInteraction;
    class ScaleInteraction* m_pScaleInteraction;
    ModelManager& m_rModelManager;
};

}