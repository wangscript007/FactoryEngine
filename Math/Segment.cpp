//
//  Segment.cpp
//  FactoryEngine
//
//  Created by Edvinas on 10/9/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#include <Math/Segment.h>

namespace ftr {
    
#define SMALL_NUM   0.00000001f

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
    if (D < SMALL_NUM) {          // the lines are almost parallel
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
    if (D < SMALL_NUM) { // the lines are almost parallel
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
    sc = (fabs(sN) < SMALL_NUM ? 0.0 : sN / sD);
    tc = (fabs(tN) < SMALL_NUM ? 0.0 : tN / tD);
    
    // get the difference of the two closest points
    glm::vec3 dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)
    
    return glm::length(dP);   // return the closest distance

}
    
    
    
}