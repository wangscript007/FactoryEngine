
#pragma once

namespace ftr {

class Geometry
{
public:
    Geometry() {};
    virtual ~Geometry() {};
    
    virtual void Rotate(const glm::vec3& oilerAngle);
    virtual void Translate(const glm::vec3& offset);
    virtual void Scale(const glm::vec3& offset);
    
    virtual void Transform(const glm::mat4& mat);

    virtual std::vector<glm::vec3>& GetPoints() { return mPoints; }
    
    glm::vec3& operator[](int index);
    
protected:
    std::vector<glm::vec3> mPoints;
};
    
inline glm::vec3& Geometry::operator[](int index)
{
    return GetPoints()[index];
}
    
    
}

