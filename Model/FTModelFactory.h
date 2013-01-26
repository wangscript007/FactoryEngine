// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

#include <Model/FTPoint.h>
#include <Model/FTFace.h>
#include <Model/FTLine.h>

class FTModelTreeManager;
//
// 
//
class FTModelFactory
{
public:
    FTModelFactory(FTModelTreeManager& rModelTreeManager);
    ~FTModelFactory() {}
    
    FTFace*     CreateRectangle(O5Vec3 vOrigin, O5Vec3 vSize) const;
    FTFace*     CreateCircle(O5Vec3 vOrigin, float fRadius, int iCount) const;
    FTFace*     CreatePolygon(std::vector<FTPoint*>& vPointsVector) const;
    FTFace*     CreateFace(O5Vec3 vOrigin, O5Vec3 vSize, FTFace::FaceType eType) const;
    FTPoint*    CreatePoint(O5Vec3 vOrigin) const;
    FTLine*     CreateLine(FTPoint* pStartPoint, FTPoint* pEndPoint) const;
    
private:
    FTModelTreeManager& m_rModelTreeManager;
};

