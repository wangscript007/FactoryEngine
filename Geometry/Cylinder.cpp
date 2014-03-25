
#include <Geometry/Cylinder.h>

namespace ftr {
    
bool Cylinder::Intersects(const Box& box) const
{
    
    if (mAxis.IntersectsBox(box)) {
        return true;
    }
    
    const glm::vec3 vertices[]= {
        // 0
        glm::vec3(
        box.mCenter.x - box.mHalfDimention.x,
        box.mCenter.y - box.mHalfDimention.y,
        box.mCenter.z + box.mHalfDimention.z),
        // 1
        glm::vec3(
        box.mCenter.x - box.mHalfDimention.x,
        box.mCenter.y + box.mHalfDimention.y,
        box.mCenter.z + box.mHalfDimention.z),
        // 2
        glm::vec3(
        box.mCenter.x + box.mHalfDimention.x,
        box.mCenter.y + box.mHalfDimention.y,
        box.mCenter.z + box.mHalfDimention.z),
        // 3
        glm::vec3(
        box.mCenter.x + box.mHalfDimention.x,
        box.mCenter.y - box.mHalfDimention.y,
        box.mCenter.z + box.mHalfDimention.z),
                          
        // 4
        glm::vec3(
        box.mCenter.x - box.mHalfDimention.x,
        box.mCenter.y - box.mHalfDimention.y,
        box.mCenter.z - box.mHalfDimention.z),
        // 5
        glm::vec3(
        box.mCenter.x - box.mHalfDimention.x,
        box.mCenter.y + box.mHalfDimention.y,
        box.mCenter.z - box.mHalfDimention.z),
        // 6
        glm::vec3(
        box.mCenter.x + box.mHalfDimention.x,
        box.mCenter.y + box.mHalfDimention.y,
        box.mCenter.z - box.mHalfDimention.z),
        // 7
        glm::vec3(
        box.mCenter.x + box.mHalfDimention.x,
        box.mCenter.y - box.mHalfDimention.y,
        box.mCenter.z - box.mHalfDimention.z)
    };
    
    static const GLubyte indices[] = {
        0, 1,   1, 2,   2, 3,   3, 0,
        4, 5,   5, 6,   6, 7,   7, 4,
        0, 4,   1, 5,   2, 6,   3, 7
    };
    
    float boxDiagonal3 = box.Diagonal3();
    
    for (int i = 0; i < 12; ++i) {
        const Segment& segment = Segment(vertices[indices[i*2]], vertices[indices[i*2 + 1]]);
        float distance = segment.DistanceFromLine(mAxis);
        if (abs(distance - mRadius) > boxDiagonal3)  {
            return false;
        }
        if (distance < mRadius) {
            return true;
        }
        
    }
    return false;
}
    
}

