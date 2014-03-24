

#include "Polyline.h"

namespace ftr {

void Polyline::AddPoint(const glm::vec3& point)
{
    mPoints.push_back(point);
}
    
void Polyline::Transform(const glm::mat4& tranformation)
{
    glm::mat3x3 m(tranformation);
    for (int i = 0; i < mPoints.size(); ++i) {
        mPoints[i] = glm::mul(mPoints[i], tranformation);
    }
}
    
    
}
