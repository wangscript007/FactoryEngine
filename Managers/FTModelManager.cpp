
#include <Managers/FTModelManager.h>

FTModelManager::FTModelManager()
{
    m_pModelTreeManager = new FTModelTreeManager();
    m_pModelFactory = new FTModelFactory(*m_pModelTreeManager);
    m_pRootGroup = new FTGroup();
    m_pModelTreeManager->SetRootNode(m_pRootGroup);
    
}

FTModelManager::~FTModelManager()
{
    FT_DELETE(m_pModelFactory);
    FT_DELETE(m_pModelTreeManager);
    FT_DELETE(m_pRootGroup);
}

#pragma mark - Instance

FTPoint* FTModelManager::NearestPointToCenterInSphere(const FTSphere& sSphere) const
{
    std::vector<FTPoint*> cPointsVector;
    FTBox sBox = sSphere.Box();
    m_pModelTreeManager->PointsInBox(sBox, cPointsVector);
    FTPoint* pNearestPoint = NULL;
    float fNearestPointDistance = MAXFLOAT;
    float fDistance;
    for(auto i = cPointsVector.begin(); i != cPointsVector.end(); ++i) {
        fDistance = (sSphere.m_vCenter - (*i)->m_vOrigin).Length();
        if (fDistance < sSphere.m_fRadius) {
            if (fDistance < fNearestPointDistance) {
                pNearestPoint = *i;
                fNearestPointDistance = fDistance;
            }
        }
    }
    return pNearestPoint;
}


