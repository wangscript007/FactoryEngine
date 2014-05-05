
#pragma once

namespace ftr {

class Geometry
{
public:
    Geometry() {};
    Geometry(const std::vector<glm::vec3>& points) : mPoints(points) {};
    
    virtual ~Geometry() {};
    
    
    virtual void Rotate(const glm::vec3& oilerAngle);
    virtual void Translate(const glm::vec3& offset);
    virtual void Scale(const glm::vec3& offset);
    
    virtual void Transform(const glm::mat4& mat);

    virtual const std::vector<glm::vec3>& GetPoints() const { return mPoints; }
    
    glm::vec3 Center() const;
    
    const glm::vec3& operator[](const int index) const;
    
protected:
    
    std::vector<glm::vec3> mPoints;
};
    
    
    
}

