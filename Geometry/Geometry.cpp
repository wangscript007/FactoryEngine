
#include <Geometry/Geometry.h>

namespace ftr {
    
void Geometry::Rotate(const glm::vec3& oilerAngle)
{
    
}

void Geometry::Translate(const glm::vec3& offset)
{
    
}

void Geometry::Scale(const glm::vec3& offset)
{
    
}
    
void Geometry::Transform(const glm::mat4& mat)
{
    std::vector<glm::vec3>& points = GetPoints();
    for (auto &p : points) {
        glm::vec4 vec(p.x, p.y, p.z, 1.0f);
        vec = vec * mat;
        p = glm::vec3(vec.x, vec.y, vec.z);
    }
}
    
const glm::vec3& Geometry::operator[](const int index)
{
    return mPoints[index];
}


}