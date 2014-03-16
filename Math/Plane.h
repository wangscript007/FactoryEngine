
#pragma once

namespace ftr {

class Plane
{
public:
    Plane() {};
    Plane(const glm::vec3& p1,const  glm::vec3& p2, const glm::vec3&  p3);
    bool Contains(const glm::vec3& p);
    
private:
    glm::vec3 mP1, mP2, mP3;
    glm::vec3 mCross;
};
    
}

