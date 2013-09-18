
#import <Utils/Picker.h>
#import <Math/GluUtils.h>
#import <OpenGL/glu.h>


namespace ftr {
        

Vec3 Picker::Viewport(const Vec3& sceneVec, const Camera::Parameters& cameraParameters)
{
    return GluProject(sceneVec, cameraParameters);
}

Vec3 Picker::Scene(const Vec3& windowVec, const Camera::Parameters& cameraParameters)
{
    float depth = DepthAtPoint(Vec2(windowVec.mX, windowVec.mY));
    return GluUnProject(Vec3(windowVec.mX, windowVec.mY, depth), cameraParameters);
}
    
Vec3 Picker::GluProject(const Vec3& sceneVec, const Camera::Parameters& cameraParameters)
{
    Vec3 windowCoords;
    GluUtils::glhProjectf(sceneVec.mX, sceneVec.mY, sceneVec.mZ,
                          reinterpret_cast<const float*>(&cameraParameters.modelviewMatrix),
                          reinterpret_cast<const float*>(&cameraParameters.projectionMatrix),
                          reinterpret_cast<const float*>(&cameraParameters.viewport),
                          reinterpret_cast<float*>(&windowCoords));
    return windowCoords;
}
    
Vec3 Picker::GluUnProject(const Vec3& windowVec, const Camera::Parameters& cameraParameters)
{
    Vec3 sceneCoords;
    GluUtils::glhUnProjectf(windowVec.mX, windowVec.mY, windowVec.mZ,
                            reinterpret_cast<const float*>(&cameraParameters.modelviewMatrix),
                            reinterpret_cast<const float*>(&cameraParameters.projectionMatrix),
                            reinterpret_cast<const float*>(&cameraParameters.viewport),
                            reinterpret_cast<float*>(&sceneCoords));
    
    
    return sceneCoords;
}

GLfloat Picker::DepthAtPoint(const Vec2& point)
{
    GLfloat depth;
    glReadPixels(point.mX, point.mY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    return depth;
}

    
}

