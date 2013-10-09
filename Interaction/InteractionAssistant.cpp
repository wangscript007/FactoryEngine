
#include <Interaction/InteractionAssistant.h>
#include <Math/Geometry.h>
#include <Utils/Picker.h>

namespace ftr {

const float InteractionAssistant::kSensitivity = 20.0f;

Vec3 InteractionAssistant::AxisAlignedViewport(const Vec3& startScene,
                                               const Vec2& endViewport,
                                               const Camera::Parameters& cameraParameters) const
{
    Vec2 startViewport = Picker::Viewport2(startScene, cameraParameters);
    Vec2 current = endViewport - startViewport;
    Vec2 zero = Picker::Viewport2(startScene, cameraParameters);
    Vec2 axisX = Picker::Viewport2(Vec3::X+startScene, cameraParameters) - zero;
    Vec2 axisY = Picker::Viewport2(Vec3::Y+startScene, cameraParameters) - zero;
    Vec2 axisZ = Picker::Viewport2(Vec3::Z+startScene, cameraParameters) - zero;
    
    glm::vec2 aX = glm::normalize(glm::vec2(axisX.mX, axisX.mY));
    glm::vec2 aY = glm::normalize(glm::vec2(axisY.mX, axisY.mY));
    glm::vec2 aZ = glm::normalize(glm::vec2(axisZ.mX, axisZ.mY));
    
    glm::vec2 curr = glm::vec2(current.mX, current.mY);
    glm::vec2 currNorm = glm::normalize(curr);
    float length = glm::length(curr);
    
    glm::vec3 perp;
    glm::vec3 angle;
    // Finding perpendiculars to axis aligned vectors
    angle.x = glm::radians(glm::orientedAngle(aX, currNorm));
    angle.y = glm::radians(glm::orientedAngle(aY, currNorm));
    angle.z = glm::radians(glm::orientedAngle(aZ, currNorm));
    
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
        axisAlignedNormal = glm::vec3(1.0f, 0.0f, 0.0f);
    } else if (min == perp.y) {
        axisAlignedNormal = glm::vec3(0.0f, 1.0f, 0.0f);
    } else if (min == perp.z) {
        axisAlignedNormal = glm::vec3(0.0f, 0.0f, 1.0f);
    }
    
    glm::vec3 startSceneGlm = glm::vec3(startScene.mX, startScene.mY, startScene.mZ);

    Segment axisAlignedSegment;
    axisAlignedSegment.mStart = startSceneGlm;
    axisAlignedSegment.mEnd = startSceneGlm + axisAlignedNormal;
    
    Segment raySegment = Picker::RayAtPoint(endViewport, cameraParameters);
    
    Segment shortestSegmentFromRay = raySegment.ShortestSegmentFromLine(axisAlignedSegment);
    
    glm::vec3 result;
    if (min == perp.x) {
        result = glm::vec3(shortestSegmentFromRay.mStart.x, startSceneGlm.y, startSceneGlm.z);
    } else if (min == perp.y) {
        result = glm::vec3(startSceneGlm.x, shortestSegmentFromRay.mStart.y, startSceneGlm.z);
    } else if (min == perp.z) {
        result = glm::vec3(startSceneGlm.x, startSceneGlm.y, shortestSegmentFromRay.mStart.z);
    }
    return Vec3(result.x, result.y, result.z);
}
    
}