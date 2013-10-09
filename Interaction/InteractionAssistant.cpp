
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
    
    glm::vec3 projection;
    glm::vec3 startSceneGlm = glm::vec3(startScene.mX, startScene.mY, startScene.mZ);
    Segment raySegment = Picker::RayAtPoint(endViewport, cameraParameters);
    glm::vec3 nearestPointOfTheRay = raySegment.NearestPoint(startSceneGlm);
    glm::vec3 completionVec = nearestPointOfTheRay - startSceneGlm;
    
    glm::vec3 normalX = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 normalY = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 normalZ = glm::vec3(0.0f, 0.0f, 1.0f);
    if (min == perp.x) {
        projection = glm::proj(completionVec, normalX);
    } else if (min == perp.y) {
        projection = glm::proj(completionVec, normalY);
    } else if (min == perp.z) {
        projection = glm::proj(completionVec, normalZ);
    }
    glm::vec3 result = startSceneGlm + projection;
    return Vec3(result.x, result.y, result.z);
}
    
}