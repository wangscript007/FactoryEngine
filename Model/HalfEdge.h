
#pragma once

#include <Model/PointNode.h>
#include <Model/FaceNode.h>

namespace ftr {

class HalfEdge
{
public:
    HalfEdge(PointNode* originNode);
    virtual ~HalfEdge();
    
    FaceNode* mIncidentFace;
    
    const glm::vec3& origin() const { return mOriginNode->mOrigin; }
    
    bool IsClockwiseCountingFrom(const HalfEdge& other) const;
    float AngleFrom(const HalfEdge& other) const;
    
    HalfEdge* twin() const { return mTwin; }
    
    void setPrev(HalfEdge* prev);
    HalfEdge* next() const { return mNext; }
    HalfEdge* prev() const { return mPrev; }
    PointNode* originNode() const { return mOriginNode; }
    void ConnectToNext(HalfEdge* next, bool connectingTwin = false);
    void MakeTwinsWith(HalfEdge* twin);
    
    void DeleteTwin() { FT_DELETE(mTwin); }
    std::string Name() const;
    std::string Description() const;
    
private:
    void SwitchNextWithPrev();

    HalfEdge* mTwin;
    PointNode* mOriginNode;
    HalfEdge* mNext;
    HalfEdge* mPrev;
    
    glm::vec3 Direction() const;

    
};
    

}

