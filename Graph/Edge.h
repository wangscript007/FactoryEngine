
#pragma once

#include <Graph/FaceNode.h>

namespace ftr {
    
class PointNode;
class LineNode;

class Edge
{
public:
    Edge(PointNode* originNode);
    virtual ~Edge();
    
    FaceNode* mIncidentFace;
    
    const glm::vec3& origin() const;
    const glm::vec3& target() const;
    
    bool IsCCWCountingFrom(const Edge& other) const;
    bool HasSameOrigin(const Edge& other) const { return mOriginNode == other.mOriginNode; }
    bool IsFree() const { return mIncidentFace == NULL; }
    float AngleFrom(const Edge& other) const;
    
    Edge* twin() const { return mTwin; }
    
    Edge* next() const { return mNext; }
    Edge* prev() const { return mPrev; }
    PointNode* originNode() const { return mOriginNode; }
    PointNode* targetNode() const { return mTwin->mOriginNode; }
    
    LineNode* lineNode() const { return mLineNode; }
    void setLineNode(LineNode* lineNode);
    
    void MakeTwinsWith(Edge* twin);
    void DeleteTwin() { FT_DELETE(mTwin); }
    void Invalidate();
    
    std::string Name() const;
    std::string Description() const;
    
    Edge* CWNeighbourWithSameOrigin();
    void ConnectToNext(Edge* other);
    void DisconnectNext() { mNext = NULL; }
    void DisconnectPrev() { mPrev = NULL; }
    
    void DoublyConnectCCWOrderedAtOrigin();

    void ReverseFaceProperties();
    
    bool mVisited;
    
private:
    
    float CCWAngleFrom(const Edge& other) const;
    void SwitchNextWithPrev();
    

    Edge* mTwin;
    PointNode* mOriginNode;
    Edge* mNext;
    Edge* mPrev;
    LineNode* mLineNode;
    
    glm::vec3 Direction() const;

    
};
    

}

