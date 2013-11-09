
#include <Model/HalfEdge.h>
#include <Math/Vector.h>

namespace ftr {
    
HalfEdge::HalfEdge(PointNode* originNode)
    :mOriginNode(originNode),
    mNext(NULL),
    mPrev(NULL),
    mTwin(NULL),
    mIncidentFace(NULL)
{
    
}
    
HalfEdge::~HalfEdge()
{

}
    
    
std::string HalfEdge::Name() const
{
    if (mOriginNode) {
        return "e" + mOriginNode->mName + "," + mTwin->mOriginNode->mName;
    }
    return "-";
}
    
std::string HalfEdge::Description() const
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

void HalfEdge::MakeTwinsWith(HalfEdge* twin)
{
    mTwin = twin;
    twin->mTwin = this;
}
        
HalfEdge* HalfEdge::CWNeighbourForNode(const PointNode& node) const
{
    HalfEdge* edge = node.mHalfEdge;
    float maxCCWAngle = 0.0f;
    HalfEdge* neighbour = edge;
    do {
        if (edge->mOriginNode == &node && edge->mPrev) {
            edge = edge->mPrev;
        } else {
            edge = edge->mTwin;
        }
        if (edge->mOriginNode == &node) {
            float CCWAngle = CCWAngleFrom(*edge);
            if (CCWAngle > maxCCWAngle) {
                maxCCWAngle = CCWAngle;
                neighbour = edge;
            }
        }
        
//        if (edge->mOriginNode == &node) {
//            printf("%s to %s CWAngle = %f \n", this->Name().c_str(), edge->Name().c_str(), CCWAngle);
//        }
    } while (edge != node.mHalfEdge);
    return neighbour;
}
    
void HalfEdge::InsertConnectionNearCWNeigbour(HalfEdge* CWNeighbour)
{
    if (CWNeighbour->mPrev) {
        CWNeighbour->mPrev->ConnectToNext(this);
    } else {
        CWNeighbour->mTwin->ConnectToNext(this);
    }
    mTwin->ConnectToNext(CWNeighbour);

}
    
float HalfEdge::CCWAngleFrom(const HalfEdge& other) const
{
    return Vector::CCWAngle(Direction(), other.Direction());
}
    
void HalfEdge::ConnectToNext(HalfEdge* next)
{
//    printf("%s to next %s\n", this->Name().c_str(), next->Name().c_str());
    assert(next);
    assert(mOriginNode != next->mOriginNode);
    mNext = next;
    mNext->mPrev = this;
}
    
glm::vec3 HalfEdge::Direction() const
{
    assert(mOriginNode);
    assert(mTwin && mTwin->mOriginNode);
    return glm::normalize(twin()->origin() - origin());
}
    
}