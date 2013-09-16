
#include <Utils/Picker.h>
#include <Math/GluUtils.h>


namespace ftr {
        

Vec3 Picker::Viewport(const Vec3& sceneVec, const Camera::Parameters& cameraParameters)
{
    Vec3 result;
    GluUtils::glhProjectf(sceneVec.mX, sceneVec.mY, sceneVec.mZ,
                          reinterpret_cast<const float*>(&cameraParameters.modelviewMatrix),
                          reinterpret_cast<const float*>(&cameraParameters.projectionMatrix),
                          reinterpret_cast<const int*>(&cameraParameters.viewport),
                          reinterpret_cast<float*>(&result));
    return result;
}

Vec3 Picker::Scene(const Vec3& windowVec, const Camera::Parameters& cameraParameters)
{
    Vec3 result;
    float depth = DepthAtPoint(Vec2(windowVec.mX, windowVec.mY));
    GluUtils::glhUnProjectf(windowVec.mX, windowVec.mY, depth,
                           reinterpret_cast<const float*>(&cameraParameters.modelviewMatrix),
                           reinterpret_cast<const float*>(&cameraParameters.projectionMatrix),
                           reinterpret_cast<const int*>(&cameraParameters.viewport),
                           reinterpret_cast<float*>(&result));
    return result;
}

GLfloat Picker::DepthAtPoint(const Vec2& point)
{
    GLfloat depth;
    glReadPixels(point.mX, point.mY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    return depth;
}

    
}

