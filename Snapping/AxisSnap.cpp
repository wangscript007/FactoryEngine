
#include <Snapping/AxisSnap.h>

namespace ftr {
    
glm::vec3 AxisSnap::Snapped() const
{
    // TODO: simplify with arrays and loops
    static glm::vec3 axisSceneX = glm::vec3(1.0f, 0.0f, 0.0f);
    static glm::vec3 axisSceneY = glm::vec3(0.0f, 1.0f, 0.0f);
    static glm::vec3 axisSceneZ = glm::vec3(0.0f, 0.0f, 1.0f);
    
    glm::vec2 startViewport = mViewport.CoordsAt(mStartScene);
    glm::vec2 currentViewport = mEndViewport - startViewport;
    glm::vec2 zeroViewport = mViewport.CoordsAt(mStartScene);
    glm::vec2 axisViewportX = mViewport.CoordsAt(axisSceneX + mStartScene) - zeroViewport;
    glm::vec2 axisViewportY = mViewport.CoordsAt(axisSceneY + mStartScene) - zeroViewport;
    glm::vec2 axisViewportZ = mViewport.CoordsAt(axisSceneZ + mStartScene) - zeroViewport;
    
    glm::vec3 perp;
    glm::vec3 angle;
    if (glm::isNull(currentViewport, 0.0f)) {
        return mEndScene;
    }
    glm::vec2 currentVNormalized = glm::normalize(currentViewport);
    angle.x = glm::radians(glm::orientedAngle(glm::normalize(axisViewportX), currentVNormalized));
    angle.y = glm::radians(glm::orientedAngle(glm::normalize(axisViewportY), currentVNormalized));
    angle.z = glm::radians(glm::orientedAngle(glm::normalize(axisViewportZ), currentVNormalized));
    float length = glm::length(currentViewport);
    perp.x = fabs(tanf(angle.x) * length);
    perp.y = fabs(tanf(angle.y) * length);
    perp.z = fabs(tanf(angle.z) * length);
    
    float min;
    min = std::min(perp.x,  perp.y);
    min = std::min(min,     perp.z);
    
    if (min > 20) {
        return mEndScene;
    }
    
    glm::vec3 axisAlignedNormal;
    if (min == perp.x) {
        axisAlignedNormal = axisSceneX;
    }
    else if (min == perp.y) {
        axisAlignedNormal = axisSceneY;
    }
    else if (min == perp.z) {
        axisAlignedNormal = axisSceneZ;
    }
    
    const Segment& axisAlignedSegment = Segment(mStartScene, mStartScene + axisAlignedNormal);
    const Segment& raySegment = mViewport.RayAtPoint(mEndViewport);
    const Segment& shortestSegmentFromRay = raySegment.ShortestSegmentFromLine(axisAlignedSegment);
    
    glm::vec3 result;
    if (min == perp.x) {
        result = glm::vec3(shortestSegmentFromRay.mStart.x, mStartScene.y, mStartScene.z);
    }
    else if (min == perp.y) {
        result = glm::vec3(mStartScene.x, shortestSegmentFromRay.mStart.y, mStartScene.z);
    }
    else if (min == perp.z) {
        result = glm::vec3(mStartScene.x, mStartScene.y, shortestSegmentFromRay.mStart.z);
    }
    return result;
}
    
}

