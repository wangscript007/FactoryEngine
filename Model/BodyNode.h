
#pragma once

#include <Model/Node.h>

namespace ftr {

class FaceNode;

class BodyNode : public Node
{
public:
    typedef         std::vector<FaceNode*> FacesVector;
    virtual         NodeType Type() const { return kBody; }
    void            Pull(FaceNode* baseFace, FaceNode* pullFace);
    void            AddFace(FaceNode* pFace);
    void            RemoveFace(FaceNode* pFace);
    
private:
    FacesVector   mFacesVector;    
};

}