

#pragma once

namespace ftr {

class Polyline
{
public:
    void AddPoint(const glm::vec3& point);
    
    std::vector<glm::vec3> mPoints;
    void Transform(const glm::mat4& tranformation);
    
private:

};
    
}

