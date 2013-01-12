// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

#include <Model/FTPoint.h>
#include <Model/FTFace.h>
#include <Model/FTLine.h>
//
// 
//
class FTModelFactory
{
public:
    FTFace*     CreateRectangleFace(O5Vec3 vOrigin, O5Vec3 vSize);
    FTPoint*    CreatePoint(O5Vec3 vOrigin);
    FTLine*     CreateLine(FTPoint* pStartPoint, FTPoint* pEndPoint);
private:
    
};

