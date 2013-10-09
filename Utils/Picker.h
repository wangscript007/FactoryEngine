#pragma once

#include <Scene/Camera.h>
#include <Math/Segment.h>

namespace ftr {

class Picker
{
public:
    static Vec3 Viewport(const Vec3& sceneVec, const Camera::Parameters& cameraParameters);
    static Vec2 Viewport2(const Vec3& sceneVec, const Camera::Parameters& cameraParameters);
    static Vec3 Scene(const Vec3& sceneVec, const Camera::Parameters& cameraParameters);
    static GLfloat DepthAtPoint(const Vec2& point);
    static Vec3 GluProject(const Vec3& sceneVec, const Camera::Parameters& cameraParameters);
    static Vec3 GluUnProject(const Vec3& windowVec, const Camera::Parameters& cameraParameters);
    static Segment RayAtPoint(const Vec2& point, const Camera::Parameters& cameraParameters);
};
    
}

