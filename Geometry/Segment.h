
#pragma once

#include <Geometry/Geometry.h>

namespace ftr {
    
class Triangle;
class Box;

class Segment : public Geometry
{
public:
    enum IntersectionSituation
    {
        kIntersectionSituationInvalid,
        kIntersectionSituationInside,
        kIntersectionSituationOutside,
        kIntersectionSituationLiesIn,
        kIntersectionSituationParallel,
        kIntersectionSituationDisjoint,

    };
    
    Segment() {};
    Segment(const glm::vec3& start, const glm::vec3& end);
    virtual ~Segment() {}
    
    glm::vec3 start() const { return mPoints[0]; }
    glm::vec3 end()   const { return mPoints[1]; }
    
    float DistanceFromPoint(const glm::vec3& point) const;
    float DistanceFromSegment(const Segment& segment) const;
    float DistanceFromLine(const Segment& segment) const;
    
    IntersectionSituation IntersectionWithTriangle(const Triangle& T, glm::vec3& I) const;
    
    Segment ShortestSegmentFromLine(const Segment& segment) const;
    
    glm::vec3 NearestPoint(const glm::vec3 &testPoint) const;
    glm::vec3 Direction() const { return end() - start(); }
    
    bool IntersectsBox(const Box& box) const;

};
    
}

