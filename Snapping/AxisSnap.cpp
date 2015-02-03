
#include <Snapping/AxisSnap.h>
#include <Geometry/Constants.h>
#include <Scene/Viewport.h>
#include <Scene/Picker.h>
#include <Processing/ModelTree.h>


namespace ftr {
    
const float kMinAxisSnappingDistanceInPixels = 20;
    
glm::vec3 AxisSnap::Snapped() const
{
    glm::vec2 startViewport = mViewport.CoordsAt(mStartScene);
    glm::vec2 currentViewport = mEndViewport - startViewport;
    glm::vec2 zeroViewport = mViewport.CoordsAt(mStartScene);
    
    glm::vec3 angle;

    if (glm::isNull(currentViewport, kEpsilonBig)) {
        return mEndScene;
    }
    
    glm::vec2 currentViewportNorm = glm::normalize(currentViewport);
    float length = glm::length(currentViewport);
    glm::vec3 perp;
    
    glm::vec3 axisAlignedNormal;
    
    float min = MAXFLOAT;
    
    for (int i = 0; i < kDimensionsCount; i++) {
        glm::vec2 viewportAxis  = mViewport.CoordsAt(kXYZAxes[i] + mStartScene) - zeroViewport;
        float angle             = glm::radians(glm::orientedAngle(glm::normalize(viewportAxis), currentViewportNorm));
        perp[i]                 = fabs(tanf(angle) * length);
        
        if (perp[i] < min) {
            min = perp[i];
            axisAlignedNormal = kXYZAxes[i];
        }
    }
    if (min > kMinAxisSnappingDistanceInPixels) {
        return mEndScene;
    }
    
    const Segment& raySegment = mViewport.RayAtPoint(mEndViewport);
    const Segment& axisAlignedSegment = Segment(mStartScene, mStartScene + axisAlignedNormal);
    const Segment& shortestSegmentFromRay = raySegment.ShortestSegmentFromLine(axisAlignedSegment);
    
    glm::vec3 result;
    for (int i = 0; i < kDimensionsCount; i++) {
        if (min == perp[i]) {
            glm::vec3 startScene = mStartScene;
            startScene[i] = shortestSegmentFromRay.mStart[i];
            result = startScene;
            break;
        }
    }
    return result;
}
    
}

