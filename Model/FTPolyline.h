
#pragma once

#include <Model/FTNode.h>
#include <Model/FTPoint.h>

class FTPolyline : FTModel
{
public:
    typedef std::vector<FTPoint*>  TPoinsVector;
    virtual ~FTPolyline() {}
    
private:
    TPoinsVector m_cPointsVector;
};

