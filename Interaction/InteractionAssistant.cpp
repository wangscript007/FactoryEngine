
#include <Interaction/InteractionAssistant.h>
#include <Math/Geometry.h>
#include <Utils/Picker.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


namespace ftr {

const float InteractionAssistant::kSensitivity = 20.0f;

Vec3 InteractionAssistant::AxisAlignedViewport(const Vec3& startScene,
                                               const Vec2& endViewport,
                                               const Camera::Parameters& cameraParameters) const
{
    Vec2 startViewport = Picker::Viewport2(startScene, cameraParameters);
    
    Vec2 zero = Picker::Viewport2(Vec3(0.0f, 0.0f, 0.0f), cameraParameters);
    Vec2 current = endViewport - startViewport;
    Vec2 axisX = Picker::Viewport2(Vec3::X, cameraParameters) - zero;
    Vec2 axisY = Picker::Viewport2(Vec3::Y, cameraParameters) - zero;
    Vec2 axisZ = Picker::Viewport2(Vec3::Z, cameraParameters) - zero;
    
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
    
    glm::vec3 normalX = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 normalY = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 normalZ = glm::vec3(0.0f, 0.0f, 1.0f);
    
    glm::vec2 projection;
//    if      (min == perp.x) projection = glm::proj(curr, normalX);
//    else if (min == perp.y) projection = glm::proj(curr, normalY);
//    else if (min == perp.z) projection = glm::proj(curr, normalZ);
    
    
// return start + projection;
    return Vec3();
}

}