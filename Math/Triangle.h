
#pragma once

namespace ftr {

class Triangle
{
public:
    Triangle() {};
    Triangle(const glm::vec3& p1,const  glm::vec3& p2, const glm::vec3&  p3);
    
    bool PlaneContains(const glm::vec3& p) const;
    std::string Description() const;
    
    glm::vec3 SurfaceNormal() const;
    
private:
    glm::vec3 mP1, mP2, mP3;
    glm::vec3 mCross;
};
    
}

