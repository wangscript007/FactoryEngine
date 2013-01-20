
#pragma once

#include <Model/FTModel.h>
#include <Model/FTPoint.h>

class FTLine : public FTModel
{
public:
    FTLine(FTPoint* pStartPoint, FTPoint* pEndPoint);
    virtual ~FTLine() {}
    
    virtual void Render();
    virtual NodeType Type() const { return kLine; }
    void SetEndPoint(FTPoint* pEndPoint) { m_pEndPoint = pEndPoint; }
    void SetStartPoint(FTPoint* pStartPoint) { m_pStartPoint = pStartPoint; }
    FTPoint* StartPoint() const { return m_pStartPoint; }
    FTPoint* EndPoint() const { return m_pEndPoint; }

private:
    FTPoint* m_pStartPoint;
    FTPoint* m_pEndPoint;
};

