
#include "Description.h"

namespace ftr {
    
std::string Description::Described(const glm::vec3 v)
{
    std::stringstream ss;
    ss << "(" <<  v.x << " | " << v.y << " | " << v.z << ")";
    return ss.str();
}

    
}