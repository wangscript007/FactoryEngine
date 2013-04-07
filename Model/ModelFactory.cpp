// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Model/ModelFactory.h>
#include <Model/Point.h>
#include <Managers/ModelTreeManager.h>

namespace Factory {

ModelFactory::ModelFactory(ModelTreeManager& rModelTreeManager)
    :m_rModelTreeManager(rModelTreeManager)
{
    
}

Face* ModelFactory::CreateRectangle(const O5Vec3& vOrigin, const O5Vec3& vSize) const
{
    std::vector<Point*> vPointsVector;
    vPointsVector.push_back(new Point(O5Vec3(vOrigin.m_fX, vOrigin.m_fY, vOrigin.m_fZ)));
    vPointsVector.push_back(new Point(O5Vec3(vOrigin.m_fX + vSize.m_fX, vOrigin.m_fY, vOrigin.m_fZ)));
    vPointsVector.push_back(new Point(O5Vec3(vOrigin.m_fX + vSize.m_fX, vOrigin.m_fY, vOrigin.m_fZ + vSize.m_fZ)));
    vPointsVector.push_back(new Point(O5Vec3(vOrigin.m_fX, vOrigin.m_fY, vOrigin.m_fZ + vSize.m_fZ)));
    return CreatePolygon(vPointsVector);
}

Face* ModelFactory::CreateCircle(O5Vec3 vOrigin, float fRadius, int iCount) const
{
    Point* pPoint;
    std::vector<Point*> vPointsVector;
    float fRadAngleStep = M_2_PI/((float)iCount);
    float fRadAngle = 0;
    float fX, fY;
    float fZ = vOrigin.m_fZ;
    for(int i = 0; i < iCount; i++) {
        fRadAngle += fRadAngleStep;
        fX = fRadius*cosf(fRadAngle);
        fY = fRadius*sinf(fRadAngle);
        pPoint = new Point();
        pPoint->m_vOrigin = O5Vec3(fX, fY, fZ);
        vPointsVector.push_back(pPoint);
    }
    return CreatePolygon(vPointsVector);
}

Face* ModelFactory::CreatePolygon(std::vector<Point*>& vPointsVector) const
{
    Face* pFace = new Face();
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

Face* ModelFactory::CreateFace(O5Vec3 vOrigin, O5Vec3 vSize, Face::FaceType eType) const
{
    switch (eType) {
        case Face::kRectangle : {
            Face* pFace = new Face();
            pFace->m_eType = Face::kRectangle;
            pFace->SetOrigin(vOrigin);
            pFace->SetSize(vSize);
            return pFace;
        } break;
        default: assert(false); break;
    }
    return NULL;
}

Point* ModelFactory::CreatePoint(O5Vec3 vOrigin) const
{
    Point* pPoint = new Point();
    pPoint->m_vOrigin = vOrigin;
    return pPoint;
}

Line* ModelFactory::CreateLine(Point* pStartPoint, Point* pEndPoint) const
{
    Line* pLine = new Line(pStartPoint, pEndPoint);
    return pLine;
}

}