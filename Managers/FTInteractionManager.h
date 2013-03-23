
#pragma once

class FTRectangleInteraction;
class FTLineInteraction;
class FTMoveInteraction;
class FTRotationInteraction;
class FTModelManager;



class FTInteractionManager
{
public:
    FTInteractionManager(FTModelManager& rModelManager);
    virtual ~FTInteractionManager();
    
    FTRectangleInteraction* RectangleInteraction() const { return m_pRectangleInteraction; }
    FTLineInteraction* LineInteraction() const { return m_pLineInteraction; }
    FTMoveInteraction* MoveInteraction() const { return m_pMoveInteraction; }
    FTRotationInteraction* RotationInteraction() const { return m_pRotationInteraction; }
    
private:
    FTRectangleInteraction* m_pRectangleInteraction;
    FTLineInteraction* m_pLineInteraction;
    FTMoveInteraction* m_pMoveInteraction;
    FTRotationInteraction* m_pRotationInteraction;
    FTModelManager& m_rModelManager;
};

