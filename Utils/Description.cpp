
#include "Description.h"

namespace ftr {
    
std::string Description::Described(const glm::vec3 v)
{
    std::stringstream ss;
    ss << "(" <<  v.x << " | " << v.y << " | " << v.z << ")";
    return ss.str();
}
    
std::string Description::Described(const glm::vec4 v)
{
    std::stringstream ss;
    ss << "(" <<  v.x << " | " << v.y << " | " << v.z << " | " << v.a << ")";
    return ss.str();
}
    
std::string Description::Described(const glm::mat4 m)
{
    std::stringstream ss;
    for (int i = 0; i < 4; ++i) {
        ss << Described(m[i]) << std::endl;
    }
    return ss.str();
}



    
}