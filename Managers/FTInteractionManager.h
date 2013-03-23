
#pragma once

class FTRectangleInteraction;
class FTLineInteraction;
class FTMoveInteraction;
class FTModelManager;



class FTInteractionManager
{
public:
    FTInteractionManager(FTModelManager& rModelManager);
    virtual ~FTInteractionManager();
    
    FTRectangleInteraction* RectangleInteraction() const { return m_pRectangleInteraction; }
    FTLineInteraction* LineInteraction() const { return m_pLineInteraction; }
    FTMoveInteraction* MoveInteraction() const { return m_pMoveInteraction; }
    
private:
    FTRectangleInteraction* m_pRectangleInteraction;
    FTLineInteraction* m_pLineInteraction;
    FTMoveInteraction* m_pMoveInteraction;
    FTModelManager& m_rModelManager;
};

