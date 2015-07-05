
#include <Geometry/Vector.h>
#include <Geometry/Constants.h>

namespace ftr {
        
    
float Vector::CWAngle(const glm::vec3& v1, const glm::vec3& v2)
{
    float angle = glm::angle(v2, v1);
    return IsCWOrder(v2, v1) ? 360.0f - angle : angle;
}
    
float Vector::CWAngle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& surfaceNormal)
{
    float angle = glm::angle(v2, v1);
    return IsCWOrder(v2, v1, surfaceNormal) ? 360.0f - angle : angle;
}
    
bool Vector::IsCWOrder(const glm::vec3& v1, const glm::vec3& v2)
{
    glm::vec3 cross = glm::cross(v1, v2);
    if (glm::isNull(cross,kEpsilonSmall)) return true;
    
    return IsCWOrder(v1, v2, XYZClosestAxis(cross));
}
    
bool Vector::IsCWOrder(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& surfaceNormal)
{
    glm::vec3 cross = glm::cross(v1, v2);
    if (glm::isNull(cross,kEpsilonSmall)) return true;
    
    return glm::dot(cross, surfaceNormal) < 0;
}
    
bool Vector::IsParallel(const glm::vec3& v1, const glm::vec3& v2)
{
    glm::vec3 cross = glm::cross(v1, v2);
    return (glm::isNull(cross, kEpsilonBig));
}
    
glm::vec3 Vector::XYZClosestAxis(glm::vec3 v)
{
    static const glm::vec3 axis[3] = { kXAxis, kYAxis, kZAxis };
    
    int maxIndex = 0;
    float max = 0;
    
    for (int i = 0; i < 3; i++) {
        float angle = glm::angle(glm::normalize(v), axis[i]);
        float diff = fabs(angle - 90.0f);
        if (diff > max) {
            max = diff;
            maxIndex = i;
        }
    }
    return axis[maxIndex];
}
    
}

