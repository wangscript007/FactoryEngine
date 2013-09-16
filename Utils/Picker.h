#pragma once

#include <Scene/Camera.h>

namespace ftr {

class Picker
{
public:
    static Vec3 Viewport(const Vec3& sceneVec, const Camera::Parameters& cameraParameters);
    static Vec3 Scene(const Vec3& sceneVec, const Camera::Parameters& cameraParameters);
    static GLfloat DepthAtPoint(const Vec2& point);
private:
    
};
    
}

