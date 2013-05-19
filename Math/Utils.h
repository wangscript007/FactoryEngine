
#pragma once

namespace ftr {

class Utils
{
public:
    static Vec3 Viewport(Vec3 sceneVec);
    static Vec3 Scene(const Vec3 windowVec);
    static GLfloat DepthAtWindowPoint(const Vec2 point);
    static void PrintMatrix(int cols, int rows, FTDouble* matrix);
};
    
}

