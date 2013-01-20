
#pragma once

#include <Model/FTNode.h>

class FTFace;

class FTBody : public FTNode
{
public:
    typedef         std::vector<FTFace*> FTFacesVector;
    virtual         NodeType Type() const { return kBody; }
    void            Pull(FTFace* baseFace, FTFace* pullFace);
    void            AddFace(FTFace* pFace);
    void            RemoveFace(FTFace* pFace);
    
private:
    FTFacesVector   m_vFacesVector;    
};

