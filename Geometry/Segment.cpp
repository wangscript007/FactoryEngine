

#include <Geometry/Segment.h>
#include <Geometry/Triangle.h>

namespace ftr {
    
const float kEpsilon = 0.00000001f;

float Segment::DistanceFromPoint(const glm::vec3& point) const
{
    return glm::length(NearestPoint(point) - point);
}
    
glm::vec3 Segment::NearestPoint(const glm::vec3 &testPoint) const
{
    const glm::vec3 A = testPoint - mStart;
    const glm::vec3 u = glm::normalize((mStart-mEnd));
    return mStart + glm::dot(A, u) * u;
};
    
Segment Segment::ShortestSegmentFromLine(const Segment& segment) const
{
    glm::vec3   u = mEnd - mStart;
    glm::vec3   v = segment.mEnd - segment.mStart;
    glm::vec3   w = mStart - segment.mStart;
    float    a = glm::dot(u,u);         // always >= 0
    float    b = glm::dot(u,v);
    float    c = glm::dot(v,v);         // always >= 0
    float    d = glm::dot(u,w);
    float    e = glm::dot(v,w);
    float    D = a*c - b*b;        // always >= 0
    float    sc, tc;
    
    // compute the line parameters of the two closest points
    if (D < kEpsilon) {          // the lines are almost parallel
        sc = 0.0;
        tc = (b>c ? d/b : e/c);    // use the largest denominator
    }
    else {
        sc = (b*e - c*d) / D;
        tc = (a*e - b*d) / D;
    }
    return Segment(mStart + (sc * u), segment.mStart + (tc * v));

}
    
float Segment::DistanceFromLine(const Segment& segment) const
{
    const Segment& shortestSegment = ShortestSegmentFromLine(segment);
    return glm::length(shortestSegment.mStart - shortestSegment.mEnd);
}
    
    
float Segment::DistanceFromSegment(const Segment& segment) const
{
    glm::vec3   u = mEnd - mStart;
    glm::vec3   v = segment.mEnd - segment.mStart;
    glm::vec3   w = mStart - segment.mStart;
    float    a = glm::dot(u,u);         // always >= 0
    float    b = glm::dot(u,v);
    float    c = glm::dot(v,v);         // always >= 0
    float    d = glm::dot(u,w);
    float    e = glm::dot(v,w);
    float    D = a*c - b*b;        // always >= 0
    float    sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
    float    tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0
    
    // compute the line parameters of the two closest points
    if (D < kEpsilon) { // the lines are almost parallel
        sN = 0.0;         // force using point P0 on segment S1
        sD = 1.0;         // to prevent possible division by 0.0 later
        tN = e;
        tD = c;
    }
    else {                 // get the closest points on the infinite lines
        sN = (b*e - c*d);
        tN = (a*e - b*d);
        if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
            sN = 0.0;
            tN = e;
            tD = c;
        }
        else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }
    
    if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
        tN = 0.0;
        // recompute sc for this edge
        if (-d < 0.0)
            sN = 0.0;
        else if (-d > a)
            sN = sD;
        else {
            sN = -d;
            sD = a;
        }
    }
    else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
        tN = tD;
        // recompute sc for this edge
        if ((-d + b) < 0.0)
            sN = 0;
        else if ((-d + b) > a)
            sN = sD;
        else {
            sN = (-d +  b);
            sD = a;
        }
    }
    // finally do the division to get sc and tc
    sc = (fabs(sN) < kEpsilon ? 0.0 : sN / sD);
    tc = (fabs(tN) < kEpsilon ? 0.0 : tN / tD);
    
    // get the difference of the two closest points
    glm::vec3 dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)
    
    return glm::length(dP);   // return the closest distance

}
    
bool Segment::IntersectsBox(const Box& box) const
{
    glm::vec3 BoxExtents, Diff;
    const glm::vec3& Dir = Direction();
    
	Diff.x = mStart.x - box.mCenter[0];
	BoxExtents.x = box.mHalfDimension[0];
    
	Diff.y = mStart.y - box.mCenter[1];
	BoxExtents.y = box.mHalfDimension[1];
    
	Diff.z = mStart.z - box.mCenter[2];
    BoxExtents.z = box.mHalfDimension[2];
    
	float fAWdU[3];
	fAWdU[0] = fabsf(Dir.x);
	fAWdU[1] = fabsf(Dir.y);
	fAWdU[2] = fabsf(Dir.z);
    
	float f;
	f = Dir.y * Diff.z - Dir.z * Diff.y;	if(fabsf(f)>BoxExtents.y*fAWdU[2] + BoxExtents.z*fAWdU[1])	return false;
	f = Dir.z * Diff.x - Dir.x * Diff.z;	if(fabsf(f)>BoxExtents.x*fAWdU[2] + BoxExtents.z*fAWdU[0])	return false;
	f = Dir.x * Diff.y - Dir.y * Diff.x;	if(fabsf(f)>BoxExtents.x*fAWdU[1] + BoxExtents.y*fAWdU[0])	return false;
    
	return true;
}
    
Segment::IntersectionSituation Segment::IntersectionWithTriangle(const Triangle& T, glm::vec3& I) const
{
    glm::vec3  u, v, n;              // triangle vectors
    glm::vec3  dir, w0, w;           // ray vectors
    float     r, a, b;              // params to calc ray-plane intersect
    
    // get triangle edge vectors and plane normal
    u = T[1] - T[0];
    v = T[2] - T[0];
    n = T.Cross();
    
    if (glm::isNull(n, kEpsilon)) {       // triangle is degenerate
        assert(false);                     // do not deal with this case
        return kIntersectionSituationInvalid;
    }
    
    dir = Direction();              // ray direction vector
    w0 = mStart - T[0];
    a = -glm::dot(n,w0);
    b = glm::dot(n,dir);
    if (fabs(b) < kEpsilon) {     // ray is  parallel to triangle plane
        if (a == 0) return kIntersectionSituationLiesIn;
        else        return kIntersectionSituationParallel;
    }
    
    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0) {                               // ray goes away from triangle
        return kIntersectionSituationDisjoint;  // => no intersect
    }
    // for a segment, also test if (r > 1.0) => no intersect
    
    I = mStart + r * dir;            // intersect point of ray and plane
    
    // is I inside T?
    float    uu, uv, vv, wu, wv, D;
    uu = glm::dot(u,u);
    uv = glm::dot(u,v);
    vv = glm::dot(v,v);
    w = I - T[0];
    wu = glm::dot(w,u);
    wv = glm::dot(w,v);
    D = uv * uv - uu * vv;
    
    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0) {
        return kIntersectionSituationOutside;
    }
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0) {
        return kIntersectionSituationOutside;
    }
    
    return kIntersectionSituationInside;                       // I is in T
}
    
    
}