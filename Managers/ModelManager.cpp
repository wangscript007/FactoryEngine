
#include <Managers/ModelManager.h>

namespace ftr {

ModelManager::ModelManager()
    :m_pSelectedNode(NULL)
{
    m_pModelTreeManager = new class ModelTreeManager();
    m_pModelFactory = new class ModelFactory(*m_pModelTreeManager);
    m_pRootGroup = new Group();
    m_pModelTreeManager->SetRootNode(m_pRootGroup);
    
}

ModelManager::~ModelManager()
{
    FT_DELETE(m_pModelFactory);
    FT_DELETE(m_pModelTreeManager);
    FT_DELETE(m_pRootGroup);
}

#pragma mark - Instance

Point* ModelManager::NearestPointToCenterInSphere(const Sphere& sSphere) const
{
    std::vector<Point*> cPointsVector;
    Box sBox = sSphere.Box();
    m_pModelTreeManager->PointsInBox(sBox, cPointsVector);
    Point* pNearestPoint = NULL;
    float fNearestPointDistance = MAXFLOAT;
    float fDistance;
    for(auto i = cPointsVector.begin(); i != cPointsVector.end(); ++i) {
        fDistance = (sSphere.m_vCenter - (*i)->m_vOrigin).Length();
        if (fDistance < sSphere.mRadius) {
            if (fDistance < fNearestPointDistance) {
                pNearestPoint = *i;
                fNearestPointDistance = fDistance;
            }
        }
    }
    return pNearestPoint;
}

void ModelManager::Select(Node* pNode)
{
    m_pSelectedNode = pNode;
}

Face* ModelManager::CreateRectangle(const Vec3& vOrigin, const Vec3& vSize) const
{
    assert(m_pSelectedNode);
    Face* pFace = m_pModelFactory->CreateRectangle(vOrigin, vSize);
    m_pSelectedNode->AddNode(pFace);
    const Face::TPointsVector& rPointsVector = pFace->PointsVector();
    for(auto i = rPointsVector.begin(); i != rPointsVector.end(); ++i) {
        m_pModelTreeManager->AddNode(*i);
    }
    return pFace;
}


Face* ModelManager::CreateFace(Vec3 vOrigin, Face::FaceType eType)
{
    assert(m_pSelectedNode);
    Face* pFace = m_pModelFactory->CreateFace(Vec3(vOrigin.mX, 0.01, vOrigin.mZ),
                                Vec3(0.0f, 0.0f, 0.0f),
                                eType);
    m_pSelectedNode->AddNode(pFace);
    return pFace;
}

Point* ModelManager::CreatePoint(Vec3 vOrigin)
{
    assert(m_pSelectedNode);
    Point* pPoint = m_pModelFactory->CreatePoint(vOrigin);
    m_pSelectedNode->AddNode(pPoint);
    m_pModelTreeManager->AddNode(pPoint);
    return pPoint;
}

Line* ModelManager::CreateLine(Point* pStartPoint, Point* pEndPoint)
{
    assert(m_pSelectedNode);
    Line* pLine = m_pModelFactory->CreateLine(pStartPoint, pEndPoint);
    m_pSelectedNode->AddNode(pLine);
    m_pSelectedNode = pLine;
    
    return pLine;
    
}
    
}

