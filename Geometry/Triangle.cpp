
#include <Geometry/Triangle.h>
#include <Utils/Description.h>

namespace ftr {
    
Triangle::Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3&  p3)
{
    mPoints.push_back(p1);
    mPoints.push_back(p2);
    mPoints.push_back(p3);
    mCross = glm::cross(p2 - p1, p3 - p1);
}
    
bool Triangle::PlaneContains(const glm::vec3& p) const
{
    glm::vec3 cross = glm::cross(mPoints[1] - p, mPoints[1] - mPoints[0]);
    return glm::isNull(glm::cross(mCross, cross), 0.3f);
}
    
glm::vec3 Triangle::SurfaceNormal() const
{
    return glm::vec3();
}
    
std::string Triangle::Description() const
{
    std::stringstream ss;
    ss << std::endl;
    for (int i = 0; i < 3; ++i) {
        ss << Description::Desribed(mPoints[i]) << std::endl;
    }
    ss << std::endl;
    return ss.str();
}
    
    

    
}

