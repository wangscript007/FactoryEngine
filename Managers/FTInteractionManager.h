
#pragma once

class FTRectangleInteraction;
class FTLineInteraction;
class FTModelManager;


class FTInteractionManager
{
public:
    FTInteractionManager(FTModelManager& rModelManager);
    virtual ~FTInteractionManager();
    
    FTRectangleInteraction* RectangleInteraction() const { return m_pRectangleInteraction; }
    FTLineInteraction* LineInteraction() const { return m_pLineInteraction; }
    
private:
    FTRectangleInteraction* m_pRectangleInteraction;
    FTLineInteraction* m_pLineInteraction;
    FTModelManager& m_rModelManager;
};

