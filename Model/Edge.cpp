
#include <Model/Edge.h>
#include <Math/Vector.h>

namespace ftr {
    
Edge::Edge(PointNode* originNode)
    :mOriginNode(originNode),
    mNext(NULL),
    mPrev(NULL),
    mTwin(NULL),
    mIncidentFace(NULL)
{
    
}
    
Edge::~Edge()
{
    if (mOriginNode && mOriginNode->mEdge == this) {
        mOriginNode->mEdge = NULL;
    }
}
    
    
std::string Edge::Name() const
{
    if (mOriginNode) {
        return "e" + mOriginNode->mName + "," + mTwin->mOriginNode->mName;
    }
    return "-";
}
    
std::string Edge::Description() const
{
    std::string description = Name();
    description += "    Next: ";
    if (mNext) {
        description += mNext->Name();
    }
    description += "    Prev: ";
    if (mPrev) {
        description += mPrev->Name();
    }
    return description;
}
    
void Edge::MakeTwinsWith(Edge* twin)
{
    assert(twin != this);
    mTwin = twin;
    twin->mTwin = this;
}
        
Edge* Edge::CWNeighbourWithSameOrigin()
{
    assert(this != mOriginNode->mEdge);
    float maxCCWAngle = 0.0f;
    Edge* edge = mOriginNode->mEdge;
    Edge* neighbour = edge;
    do {
        if (edge->mOriginNode == mOriginNode) {
            float CCWAngle = CCWAngleFrom(*edge);
            if (CCWAngle > maxCCWAngle) {
                maxCCWAngle = CCWAngle;
                neighbour = edge;
            }
        }
        if (edge->mOriginNode == mOriginNode && edge->mPrev) {
            edge = edge->mPrev;
        } else {
            edge = edge->mTwin;
        }
        printf("Edge %s\n", edge->Name().c_str());
    } while (edge != mOriginNode->mEdge);
    printf("Edge %s CW neighbour %s\n", Name().c_str(), neighbour->Name().c_str());
    return neighbour;
}
    

// Connect 2 pairs of edges
void Edge::DoublyConnectCCWOrderedAtOrigin()
{
    ftr::Edge* CWNeighbour = CWNeighbourWithSameOrigin();
    // Notice: use old prev pointer pointer to connect edge
    if (CWNeighbour->prev()) {
        CWNeighbour->prev()->ConnectToNext(this);
    } else {
        CWNeighbour->twin()->ConnectToNext(this);
    }
    // Notice: overwrite prev pointer by connecting twin
    mTwin->ConnectToNext(CWNeighbour);
}
    
float Edge::CCWAngleFrom(const Edge& other) const
{
    return Vector::CCWAngle(Direction(), other.Direction());
}
    
void Edge::ConnectToNext(Edge* next)
{
    printf("%s to next %s\n", this->Name().c_str(), next->Name().c_str());
    assert(next);
    assert(next != this);
    assert(next != mTwin);
    assert(mOriginNode != next->mOriginNode);
    
    mNext = next;
    mNext->mPrev = this;
}
    
glm::vec3 Edge::Direction() const
{
    assert(mOriginNode);
    assert(mTwin && mTwin->mOriginNode);
    return glm::normalize(twin()->origin() - origin());
}
    
}