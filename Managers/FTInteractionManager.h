
#pragma once

class FTRectangleInteraction;
class FTModelManager;

class FTInteractionManager
{
public:
    FTInteractionManager(FTModelManager& rModelManager);
    virtual ~FTInteractionManager();
    
    FTRectangleInteraction* RectangleInteraction() const { return m_pRectangleInteraction; }
    
private:
    FTRectangleInteraction* m_pRectangleInteraction;
    FTModelManager& m_rModelManager;
};

