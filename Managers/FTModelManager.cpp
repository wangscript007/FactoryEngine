
#include <Managers/FTModelManager.h>

FTModelManager::FTModelManager()
    :m_pSelectedNode(NULL)
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

void FTModelManager::Select(FTNode* pNode)
{
    m_pSelectedNode = pNode;
}

FTFace* FTModelManager::CreateRectangle(const O5Vec3& vOrigin, const O5Vec3& vSize) const
{
    assert(m_pSelectedNode);
    FTFace* pFace = m_pModelFactory->CreateRectangle(vOrigin, vSize);
    m_pSelectedNode->AddNode(pFace);
    const FTFace::TPointsVector& rPointsVector = pFace->PointsVector();
    for(auto i = rPointsVector.begin(); i != rPointsVector.end(); ++i) {
        m_pModelTreeManager->AddNode(*i);
    }
    return pFace;
}


FTFace* FTModelManager::CreateFace(O5Vec3 vOrigin, FTFace::FaceType eType)
{
    assert(m_pSelectedNode);
    FTFace* pFace = m_pModelFactory->CreateFace(O5Vec3(vOrigin.m_fX, 0.01, vOrigin.m_fZ),
                                O5Vec3(0.0f, 0.0f, 0.0f),
                                eType);
    m_pSelectedNode->AddNode(pFace);
    return pFace;
}

FTPoint* FTModelManager::CreatePoint(O5Vec3 vOrigin)
{
    assert(m_pSelectedNode);
    FTPoint* pPoint = m_pModelFactory->CreatePoint(vOrigin);
    m_pSelectedNode->AddNode(pPoint);
    m_pModelTreeManager->AddNode(pPoint);
    return pPoint;
}

FTLine* FTModelManager::CreateLine(FTPoint* pStartPoint, FTPoint* pEndPoint)
{
    assert(m_pSelectedNode);
    FTLine* pLine = m_pModelFactory->CreateLine(pStartPoint, pEndPoint);
    m_pSelectedNode->AddNode(pLine);
    m_pSelectedNode = pLine;
    
    return pLine;
    
}

