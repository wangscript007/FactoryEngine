
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
    description += "    Twin: ";
    if (mTwin) {
        description += mTwin->Name();
    }
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

void HalfEdge::setTwin(HalfEdge* twin)
{
    mTwin = twin;
    twin->mTwin = this;
}
    
void HalfEdge::setPrev(HalfEdge* prev)
{
    if (!prev) return;
    
    mPrev = prev;
    prev->mNext = this;
    
    if (mTwin) {
        mTwin->mNext = prev->mTwin;
        prev->mTwin->mPrev = mTwin;
    }
}
    

    
void HalfEdge::Reverse()
{
    assert(mTwin != this);
    if (mOriginNode->mHalfEdge == this) {
        mOriginNode->mHalfEdge = mTwin;
    }
    if (mTwin->mOriginNode->mHalfEdge == mTwin) {
        mTwin->mOriginNode->mHalfEdge = this;
    }
    
    std::swap(mOriginNode, mTwin->mOriginNode);
    std::swap(mNext, mPrev);
    std::swap(mTwin->mNext, mTwin->mPrev);
}
    
    
bool HalfEdge::IsClockwiseFrom(const HalfEdge& other) const
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