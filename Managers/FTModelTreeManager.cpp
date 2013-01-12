
#include <Managers/FTModelTreeManager.h>


FTModelTreeManager::FTModelTreeManager()
{
    m_pOctree = new FTOctree(FTBox(O5Vec3(0.0f, 0.0f, 0.0f), O5Vec3(8.0f, 8.0f, 8.0f)));
}

FTModelTreeManager::~FTModelTreeManager()
{
    delete m_pOctree;
}

#pragma mark Instance

void FTModelTreeManager::SetRootNode(FTNode *pRootNode)
{
    m_pRootNode = pRootNode;
}


