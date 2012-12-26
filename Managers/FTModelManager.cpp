
#include <FactoryEngine.h>

FTModelManager::FTModelManager()
{
    m_pModelFactory = new FTModelFactory();
    m_pModelTreeManager = new FTModelTreeManager();
    m_pRootGroup = new FTGroup();
    m_pModelTreeManager->SetRootNode(m_pRootGroup);
    
}

FTModelManager::~FTModelManager()
{
    delete m_pModelFactory;
    delete m_pModelTreeManager;
}

#pragma mark - Instance



