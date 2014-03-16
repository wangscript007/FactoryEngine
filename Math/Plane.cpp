
#include <Math/Plane.h>

namespace ftr {
    
Plane::Plane(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3&  p3) :
mP1(p1), mP2(p2), mP3(p3)
{
    mCross = glm::cross(p2 - p1, p3 - p1);
}
    
bool Plane::Contains(const glm::vec3& p)
{
    glm::vec3 cross = glm::cross(mP2 - p, mP2 - mP1);
    return glm::isNull(glm::cross(mCross, cross), 0.000001f);
}
    
}

