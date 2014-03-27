
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
    for (int i = 0; i < points.size(); ++i) {
        glm::vec4 vec(points[i].x, points[i].y, points[i].z, 1.0f);
        vec = vec * mat;
        points[i] = glm::vec3(vec.x, vec.y, vec.z);
    }
}

}