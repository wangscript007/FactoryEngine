
#import <Utils/Picker.h>
#import <OpenGL/glu.h>


namespace ftr {
        

glm::vec3 Picker::Viewport(const glm::vec3& sceneVec, const Camera::Parameters& cameraParameters)
{
    return GluProject(sceneVec, cameraParameters);
}
    
glm::vec2 Picker::Viewport2(const glm::vec3& sceneVec, const Camera::Parameters& cameraParameters)
{
    glm::vec3 vec3 = Picker::Viewport(sceneVec, cameraParameters);
    return glm::vec2(vec3.x, vec3.y);
}

glm::vec3 Picker::Scene(const glm::vec3& windowVec, const Camera::Parameters& cameraParameters)
{
    float depth = DepthAtPoint(glm::vec2(windowVec.x, windowVec.y));
    return GluUnProject(glm::vec3(windowVec.x, windowVec.y, depth), cameraParameters);
}
    
glm::vec3 Picker::GluProject(const glm::vec3& sceneVec, const Camera::Parameters& cameraParameters)
{
    return glm::project(sceneVec,
                        cameraParameters.modelviewMatrix,
                        cameraParameters.projectionMatrix,
                        cameraParameters.viewport);
    
}
    
glm::vec3 Picker::GluUnProject(const glm::vec3& windowVec, const Camera::Parameters& cameraParameters)
{
    return glm::unProject(windowVec,
                          cameraParameters.modelviewMatrix,
                          cameraParameters.projectionMatrix,
                          cameraParameters.viewport);
}

GLfloat Picker::DepthAtPoint(const glm::vec2& point)
{
    GLfloat depth;
    glReadPixels(point.x, point.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    return depth;
}
    
Segment Picker::RayAtPoint(const glm::vec2& point, const Camera::Parameters& cameraParameters)
{
    Segment ray;
    glm::vec3 start = GluUnProject(glm::vec3(point.x, point.y, 0.1), cameraParameters);
    glm::vec3 end = GluUnProject(glm::vec3(point.x, point.y, 0.9), cameraParameters);
    ray.mStart = glm::vec3(start.x, start.y, start.z);
    ray.mEnd = glm::vec3(end.x, end.y, end.z);
    return ray;
}
    
}

