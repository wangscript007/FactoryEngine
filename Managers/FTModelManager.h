
#pragma once

#include "../Model/FTModelFactory.h"
#include "../Model/FTGroup.h"
#include "FTModelTreeManager.h"

class FTModelManager
{
public:
                            FTModelManager();
                            ~FTModelManager();
    
    FTModelFactory*         ModelFactory() const { return m_pModelFactory; }
    FTModelTreeManager*     ModelTreeManager() const { return  m_pModelTreeManager; }
    
private:
    FTModelFactory*         m_pModelFactory;
    FTModelTreeManager*     m_pModelTreeManager;
    FTGroup*                m_pRootGroup;
};

