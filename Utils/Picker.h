#pragma once

namespace ftr {

class Picker
{
public:
    static Vec3 Viewport(const Vec3& sceneVec);
    static Vec3 Scene(const Vec3& windowVec);
    static GLfloat DepthAtPoint(const Vec2& point);
private:
    
};
    
}

