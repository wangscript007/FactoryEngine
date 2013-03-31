
#pragma once

class FTUtils
{
public:
    static O5Vec3 Viewport(O5Vec3 sceneVec);
    static O5Vec3 Scene(const O5Vec3 windowVec);
    static GLfloat DepthAtWindowPoint(const O5Vec2 point);
    static void PrintMatrix(int cols, int rows, GLdouble* matrix);
};

