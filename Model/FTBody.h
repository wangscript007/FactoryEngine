
#pragma once

#include <Model/FTNode.h>

class FTFace;

class FTBody : public FTNode
{
public:
    typedef         std::vector<FTFace*> FTFacesVector;
    void            Pull(FTFace* baseFace, FTFace* pullFace);
    void            AddFace(FTFace* pFace);
    void            RemoveFace(FTFace* pFace);
    
private:
    FTFacesVector   m_vFacesVector;    
};

