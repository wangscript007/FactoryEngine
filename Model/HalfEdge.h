
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
    
    bool IsCWCountingFrom(const HalfEdge& other) const;
    bool HasSameOrigin(const HalfEdge& other) const { return mOriginNode == other.mOriginNode; }
    bool HasFreeNextEdge() const { return next() && next() && !next()->mIncidentFace; }
    float AngleFrom(const HalfEdge& other) const;
    
    HalfEdge* twin() const { return mTwin; }
    
    void setPrev(HalfEdge* prev);
    HalfEdge* next() const { return mNext; }
    HalfEdge* prev() const { return mPrev; }
    PointNode* originNode() const { return mOriginNode; }
    
    void MakeTwinsWith(HalfEdge* twin);
    void DeleteTwin() { FT_DELETE(mTwin); }
    
    std::string Name() const;
    std::string Description() const;
    
    HalfEdge* CWNeighbourForNode(const PointNode& node) const;
    void ConnectToNext(HalfEdge* other);
    
    void InsertConnectionNearCWNeigbour(HalfEdge* CWNeighbour);
    
private:
    
    float CCWAngleFrom(const HalfEdge& other) const;
    void SwitchNextWithPrev();
    

    HalfEdge* mTwin;
    PointNode* mOriginNode;
    HalfEdge* mNext;
    HalfEdge* mPrev;
    
    glm::vec3 Direction() const;

    
};
    

}

