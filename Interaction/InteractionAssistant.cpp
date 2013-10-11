
#include <Interaction/InteractionAssistant.h>
#include <Math/Geometry.h>
#include <Utils/Picker.h>

namespace ftr {

const float InteractionAssistant::kSensitivity = 20.0f;

glm::vec3 InteractionAssistant::AxisAlignedViewport(const glm::vec3& startScene,
                                                    const glm::vec2& endViewport,
                                                    const Camera::Parameters& cameraParameters) const
{
    static glm::vec3 axisSceneX = glm::vec3(1.0f, 0.0f, 0.0f);
    static glm::vec3 axisSceneY = glm::vec3(0.0f, 1.0f, 0.0f);
    static glm::vec3 axisSceneZ = glm::vec3(0.0f, 0.0f, 1.0f);
    
    glm::vec2 startViewport = Picker::Viewport2(startScene, cameraParameters);
    glm::vec2 currentViewport = endViewport - startViewport;
    glm::vec2 zeroViewport = Picker::Viewport2(startScene, cameraParameters);
    glm::vec2 axisViewportX = Picker::Viewport2(axisSceneX + startScene, cameraParameters) - zeroViewport;
    glm::vec2 axisViewportY = Picker::Viewport2(axisSceneY + startScene, cameraParameters) - zeroViewport;
    glm::vec2 axisViewportZ = Picker::Viewport2(axisSceneZ + startScene, cameraParameters) - zeroViewport;
    
    glm::vec3 perp;
    glm::vec3 angle;
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
    
    if (min > kSensitivity) {
        return startScene;
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
    
    const Segment& axisAlignedSegment = Segment(startScene, startScene + axisAlignedNormal);
    const Segment& raySegment = Picker::RayAtPoint(endViewport, cameraParameters);
    const Segment& shortestSegmentFromRay = raySegment.ShortestSegmentFromLine(axisAlignedSegment);
    
    glm::vec3 result;
    if (min == perp.x) {
        result = glm::vec3(shortestSegmentFromRay.mStart.x, startScene.y, startScene.z);
    }
    else if (min == perp.y) {
        result = glm::vec3(startScene.x, shortestSegmentFromRay.mStart.y, startScene.z);
    }
    else if (min == perp.z) {
        result = glm::vec3(startScene.x, startScene.y, shortestSegmentFromRay.mStart.z);
    }
    return result;
}
    
}