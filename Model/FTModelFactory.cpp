// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <FactoryEngine.h>

FTFace* FTModelFactory::CreateRectangleFace(O5Vec3 vOrigin, O5Vec3 vSize)
{
    FTFace* pFace = new FTFace();
    pFace->m_eType = FTFace::FTRectangle;
    pFace->m_vOrigin = vOrigin;
    pFace->m_vSize = vSize;
    return pFace;
}

FTPoint* FTModelFactory::CreatePoint(O5Vec3 vOrigin)
{
    FTPoint* pPoint = new FTPoint();
    pPoint->SetOrigin(vOrigin);
    /*
    pFace->m_vSize = vSize;
    */
    return pPoint;
}


// creates object of unit size
/*
FTModel* FTModelFactory::CreateModel(FTModelType objectType)
{
    FTModel* object = NULL;
    switch (objectType) {
        case kFTModelTypeCube: {
            object = new FTModel();
            FTVec3d vertices[] = 
            {
                {1,1,1},    {-1,1,1},   {-1,-1,1},  {1,-1,1},           // v0-v1-v2-v3
                {1,1,1},    {1,-1,1},   {1,-1,-1},  {1,1,-1},           // v0-v3-v4-v5
                {1,1,1},    {1,1,-1},   {-1,1,-1},  {-1,1,1},           // v0-v5-v6-v1
                {-1,1,1},   {-1,1,-1},  {-1,-1,-1}, {-1,-1,1},          // v1-v6-v7-v2
                {-1,-1,-1}, {1,-1,-1},  {1,-1,1},   {-1,-1,1},          // v7-v4-v3-v2
                {1,-1,-1},  {-1,-1,-1}, {-1,1,-1},  {1,1,-1}            // v4-v7-v6-v5
            };
        } break;
    }
    return object;
}
*/