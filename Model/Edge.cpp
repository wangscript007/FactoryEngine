
#include <Model/Edge.h>
#include <Geometry/Vector.h>
#include <Model/PointNode.h>

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
    
const glm::vec3& Edge::origin() const
{
    return mOriginNode->mOrigin;
}
    
const glm::vec3& Edge::target() const
{
    return targetNode()->mOrigin;
}
    
std::string Edge::Name() const
{
    
    if (mOriginNode) {
        std::string str = "e" + mOriginNode->mName + "," + mTwin->mOriginNode->mName;
        if (mIncidentFace) {
            str += "i";
        }
        return str;
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
        if (edge->mOriginNode == mOriginNode && edge->IsFree()) {
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
    } while (edge != mOriginNode->mEdge);
    return neighbour;
}


// Connect 2 pairs of edges
// This method only works in 2D?
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
    
bool Edge::IsCCWCountingFrom(const Edge& other) const
{
    
    bool result = Vector::IsCWOrder(Direction(), other.Direction());
    if (result) {
        printf("%s is CCW from %s.\n", Name().c_str(), other.Name().c_str());
    } else {
        printf("%s is CW from %s.\n", Name().c_str(), other.Name().c_str());
    }
    return result;
}
    
void Edge::ConnectToNext(Edge* next)
{
    printf("%s connect to next %s\n", Name().c_str(), next->Name().c_str());
    assert(next);
    assert(next != this);
    assert(next != mTwin);
    //assert(!mIncidentFace);
    //assert(!next->mIncidentFace);
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