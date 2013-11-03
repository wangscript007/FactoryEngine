
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
    
void HalfEdge::ConnectToNext(HalfEdge* next, bool connectingTwin)
{
    if (!connectingTwin) {
        printf("%s to %s\n", this->Name().c_str(), next->Name().c_str());
    }
    mNext = next;
    mNext->mPrev = this;
    
    
    if (!connectingTwin) {
        mNext->mTwin->ConnectToNext(mTwin, true);
    }
}
    
    
bool HalfEdge::IsClockwiseCountingFrom(const HalfEdge& other) const
{
    return Vector::IsCWOrder(other.Direction(), Direction());
}
    
float HalfEdge::AngleFrom(const HalfEdge& other) const
{
    return glm::angle(other.Direction(), Direction());
}
    
glm::vec3 HalfEdge::Direction() const
{
    assert(mOriginNode);
    assert(mTwin && mTwin->mOriginNode);
    return glm::normalize(twin()->origin() - origin());
}
    
}