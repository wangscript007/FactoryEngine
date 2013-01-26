// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Model/FTModelFactory.h>
#include <Model/FTPoint.h>
#include <Managers/FTModelTreeManager.h>


FTModelFactory::FTModelFactory(FTModelTreeManager& rModelTreeManager)
    :m_rModelTreeManager(rModelTreeManager)
{
    
}

FTFace* FTModelFactory::CreateRectangle(const O5Vec3& vOrigin, const O5Vec3& vSize) const
{
    std::vector<FTPoint*> vPointsVector;
    vPointsVector.push_back(new FTPoint(O5Vec3(vOrigin.m_fX, vOrigin.m_fY, vOrigin.m_fZ)));
    vPointsVector.push_back(new FTPoint(O5Vec3(vOrigin.m_fX + vSize.m_fX, vOrigin.m_fY, vOrigin.m_fZ)));
    vPointsVector.push_back(new FTPoint(O5Vec3(vOrigin.m_fX + vSize.m_fX, vOrigin.m_fY, vOrigin.m_fZ + vSize.m_fZ)));
    vPointsVector.push_back(new FTPoint(O5Vec3(vOrigin.m_fX, vOrigin.m_fY, vOrigin.m_fZ + vSize.m_fZ)));
    return CreatePolygon(vPointsVector);
}

FTFace* FTModelFactory::CreateCircle(O5Vec3 vOrigin, float fRadius, int iCount) const
{
    FTPoint* pPoint;
    std::vector<FTPoint*> vPointsVector;
    float fRadAngleStep = M_2_PI/((float)iCount);
    float fRadAngle = 0;
    float fX, fY;
    float fZ = vOrigin.m_fZ;
    for(int i = 0; i < iCount; i++) {
        fRadAngle += fRadAngleStep;
        fX = fRadius*cosf(fRadAngle);
        fY = fRadius*sinf(fRadAngle);
        pPoint = new FTPoint();
        pPoint->m_vOrigin = O5Vec3(fX, fY, fZ);
        vPointsVector.push_back(pPoint);
    }
    return CreatePolygon(vPointsVector);
}

FTFace* FTModelFactory::CreatePolygon(std::vector<FTPoint*>& vPointsVector) const
{
    FTFace* pFace = new FTFace();
    for(int i = 0; i < vPointsVector.size(); i++) {
        pFace->AddPoint(vPointsVector[i]);
        if (i > 0) {
            pFace->AddLine(CreateLine(vPointsVector[i], vPointsVector[i-1]));
        }
    }
    // Closing line
    size_t iSize = vPointsVector.size();
    pFace->AddLine(CreateLine(vPointsVector[iSize-1], vPointsVector[0]));
    return pFace;
}

FTFace* FTModelFactory::CreateFace(O5Vec3 vOrigin, O5Vec3 vSize, FTFace::FaceType eType) const
{
    switch (eType) {
        case FTFace::kRectangle : {
            FTFace* pFace = new FTFace();
            pFace->m_eType = FTFace::kRectangle;
            pFace->SetOrigin(vOrigin);
            pFace->SetSize(vSize);
            return pFace;
        } break;
        default: assert(false); break;
    }
    return NULL;
}

FTPoint* FTModelFactory::CreatePoint(O5Vec3 vOrigin) const
{
    FTPoint* pPoint = new FTPoint();
    pPoint->m_vOrigin = vOrigin;
    return pPoint;
}

FTLine* FTModelFactory::CreateLine(FTPoint* pStartPoint, FTPoint* pEndPoint) const
{
    FTLine* pLine = new FTLine(pStartPoint, pEndPoint);
    return pLine;
}
