// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Model/FTModelFactory.h>
#include <Managers/FTModelTreeManager.h>

FTModelFactory::FTModelFactory(FTModelTreeManager& rModelTreeManager)
    :m_rModelTreeManager(rModelTreeManager)
{
    
}

FTFace* FTModelFactory::CreateFace(O5Vec3 vOrigin, O5Vec3 vSize, FTFace::FaceType eType) const
{
    switch (eType) {
        case FTFace::kRectangle : {
            FTFace* pFace = new FTFace();
            pFace->m_eType = FTFace::kRectangle;
            pFace->m_vOrigin = vOrigin;
            pFace->m_vSize = vSize;
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
