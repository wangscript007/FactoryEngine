
#include <Utils/Picker.h>

namespace ftr {
        
Vec3 Picker::Viewport(const Vec3& sceneVec)
{
    GLint viewport[4];
    Mat4 modelviewMatrix[16];
    Mat4 projectionMatrix[16];
    glGetIntegerv (GL_VIEWPORT, viewport);
    double x = sceneVec.mX;
    double y = sceneVec.mY;
    double z = sceneVec.mZ;
    double resultX, resultY, resultZ;
    /*
    gluProject(x, y, z,
               modelviewMatrix, projectionMatrix, viewport,
               &resultX, &resultY, &resultZ);
    */
    return Vec3(0, 0, 0);
}

Vec3 Picker::Scene(const Vec3& windowVec)
{
    Frame viewport;
    Mat4 modelviewMatrix;
    Mat4 projectionMatrix;
    //glGetIntegerv (GL_VIEWPORT, viewport);
    GLfloat depth = DepthAtPoint(Vec2(windowVec.mX, windowVec.mY));
    double x = windowVec.mX;
    double y = windowVec.mY;
    double resultX, resultY, resultZ;
    /*
    gluUnProject(x, y, depth,
                 modelviewMatrix, projectionMatrix, viewport,
                 &resultX, &resultY, &resultZ);
    */
    return Vec3(0, 0, 0);
}

GLfloat Picker::DepthAtPoint(const Vec2& point)
{
    GLfloat depth;
    glReadPixels(point.mX, point.mY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    return depth;
}

    
}

