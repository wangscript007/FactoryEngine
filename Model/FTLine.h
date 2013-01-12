
#pragma once

#include <Model/FTModel.h>
#include <Model/FTPoint.h>

class FTLine : public FTModel
{
public:
    FTLine(FTPoint* pStartPoint, FTPoint* pEndPoint);
    virtual ~FTLine() {}
    
    virtual void Render();

private:
    FTPoint* m_pStartPoint;
    FTPoint* m_pEndPoint;
};

