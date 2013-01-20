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
    
    FTFace*     CreateFace(O5Vec3 vOrigin, O5Vec3 vSize, FTFace::FaceType eType) const;
    FTPoint*    CreatePoint(O5Vec3 vOrigin) const;
    FTLine*     CreateLine(FTPoint* pStartPoint, FTPoint* pEndPoint) const;
    
private:
    FTModelTreeManager& m_rModelTreeManager;
};

