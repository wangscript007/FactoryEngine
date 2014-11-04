
#include <Geometry/Geometry.h>
#include <Utils/Description.h>


namespace ftr {

void Geometry::Rotate(float angle, const glm::vec3& aroundVector)
{
    Transform(glm::rotate(angle, aroundVector));
}
    
void Geometry::Translate(const glm::vec3& offset)
{
    for (auto &p : mPoints) {
        p += offset;
    }
}
    
void Geometry::Scale(const glm::vec3& scale)
{
    Transform(glm::scale(scale));
}

void Geometry::Scale(const glm::vec3& scale, const glm::vec3& center)
{
    Translate(center);
    Scale(scale);
    Translate(-center);
}
     
void Geometry::Transform(const glm::mat4& mat)
{
    for (auto &p : mPoints) {
        glm::vec4 vec(p.x, p.y, p.z, 1.0f);
        vec = mat * vec;
        p = glm::vec3(vec.x, vec.y, vec.z);
    }
}
    
glm::vec3 Geometry::Center() const
{
    glm::vec3 sum;
    for (auto &p : mPoints) {
        sum += p;
    }
    return sum/static_cast<float>(mPoints.size());
}
    
const glm::vec3& Geometry::operator[](const int index) const
{
    return mPoints[index];
}
    
bool Geometry::IsEqual(const Geometry& other, float epsilon) const
{
    for (int i = 0; i < mPoints.size(); ++i) {
        if (!glm::isNull(mPoints[i] - other[i], epsilon)) {
            return false;
        }
    }
    return true;
}
    


}