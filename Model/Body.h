
#pragma once

#include <Model/Node.h>

namespace Factory {

class Face;

class Body : public Node
{
public:
    typedef         std::vector<Face*> FacesVector;
    virtual         NodeType Type() const { return kBody; }
    void            Pull(Face* baseFace, Face* pullFace);
    void            AddFace(Face* pFace);
    void            RemoveFace(Face* pFace);
    
private:
    FacesVector   m_vFacesVector;    
};

}