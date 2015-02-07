
#pragma once


namespace ftr {

class Vector
{
public:
    virtual ~Vector() {}
    static bool IsCWOrder(const glm::vec3& v1, const glm::vec3& v2);
    static bool IsCWOrder(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& surfaceNormal);
    static float CWAngle(const glm::vec3& v1, const glm::vec3& v2);
    static float CWAngle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& surfaceNormal);
    static glm::vec3 XYZClosestAxis(glm::vec3 v);
    static bool IsParallel(const glm::vec3& v1, const glm::vec3& v2);
private:
    
    
};
    
}

