
#pragma once


#include <Geometry/Geometry.h>

namespace ftr {

class Triangle: public Geometry
{
public:
    Triangle() {};
    Triangle(const glm::vec3& p1,const  glm::vec3& p2, const glm::vec3&  p3);
    Triangle(const std::vector<glm::vec3>& points) : Geometry(points) {};
    
    bool PlaneContains(const glm::vec3& p) const;
    std::string Description() const;
    glm::vec3 SurfaceNormal() const;
    glm::vec3 Cross() const;
    
    static bool IsInOneLine(const glm::vec3& p1,const  glm::vec3& p2, const glm::vec3&  p3);
    
    
private:
    
    
    glm::vec3 mCross;
};
    
}

