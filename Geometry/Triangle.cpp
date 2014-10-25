
#include <Geometry/Triangle.h>
#include <Utils/Description.h>
#include <Geometry/Vector.h>

namespace ftr {
    
bool Triangle::IsInOneLine(const glm::vec3& p1,const  glm::vec3& p2, const glm::vec3&  p3)
{
    return glm::isNull(glm::cross(p2 - p1, p3 - p2), 0.0000001f);
}
    
Triangle::Triangle(const std::vector<glm::vec3>& points)
    : Geometry(points)
{
    // points can't be in one line
    assert(!glm::isNull(Cross(), 0.0000001f));

}
    
Triangle::Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3&  p3)
{
    mPoints.push_back(p1);
    mPoints.push_back(p2);
    mPoints.push_back(p3);
    
    // points can't be in one line
    assert(!glm::isNull(Cross(), 0.0000001f));
    
}
    
bool Triangle::PlaneContains(const glm::vec3& p) const
{
    glm::vec3 cross = glm::cross(mPoints[1] - p, mPoints[1] - mPoints[0]);
    glm::vec3 surfaceNormal = SurfaceNormal();
    return glm::isNull(glm::cross(surfaceNormal, cross), 0.01f);
}
    
glm::vec3 Triangle::SurfaceNormal() const
{
    return glm::normalize(Cross());
}
    
glm::vec3 Triangle::Cross() const
{
    return glm::cross(mPoints[1] - mPoints[0], mPoints[2] - mPoints[0]);
}
    
bool Triangle::IsParallelTo(const Triangle& other) const
{
    return  glm::isNull(glm::cross(SurfaceNormal(), other.SurfaceNormal()), 0.00001f);
}

Triangle Triangle::MoveToPoint(const glm::vec3& vec) const
{
    return Triangle();
}
    
std::string Triangle::Description() const
{
    std::stringstream ss;
    ss << std::endl;
    for (int i = 0; i < 3; ++i) {
        ss << Description::Described(mPoints[i]) << std::endl;
    }
    ss << std::endl;
    return ss.str();
}
    

}

