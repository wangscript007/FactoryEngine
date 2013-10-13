
#include <Scene/Viewport.h>

namespace ftr {
    
std::vector<glm::vec3> Viewport::mDebugPoints;
    
void Viewport::AddDebugPoint(const glm::vec2& point)
{
    mDebugPoints.push_back(glm::vec3(point.x, point.y, DepthAtPoint(point)));
}

float Viewport::DepthAtPoint(const glm::vec2& point)
{
#ifdef TEST
    for(auto it = mDebugPoints.begin(); it != mDebugPoints.end(); ++it)
    {
        glm::vec3 test = *it;
        glm::detail::tvec2<bool> equal = glm::epsilonEqual(point, glm::vec2(test.x, test.y), 0.0001f);
        if (equal.x && equal.y) {
            return test.z;
        }
    }
    assert(false);
#endif
    float depth;
    glReadPixels(point.x, point.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    return depth;
}

glm::vec2 Viewport::CoordsAt(const glm::vec3& sceneCoords) const
{
    glm::vec3 result =  Project(sceneCoords);
    return glm::vec2(result.x, result.y);
}
    
glm::vec3 Viewport::SceneCoordsAt(const glm::vec2& viewportCoords) const
{
    return UnProject(glm::vec3(viewportCoords.x, viewportCoords.y, DepthAtPoint(viewportCoords)));
}
    
Segment Viewport::RayAtPoint(const glm::vec2& point) const
{
    return Segment(UnProject(glm::vec3(point.x, point.y, 0.0f)),
                   UnProject(glm::vec3(point.x, point.y, 1.0f)));
}

glm::vec3 Viewport::Project(const glm::vec3& sceneVec) const
{
    return glm::project(sceneVec, modelviewMatrix, projectionMatrix, frame);
    
}

glm::vec3 Viewport::UnProject(const glm::vec3& windowVec) const
{
    return glm::unProject(windowVec, modelviewMatrix, projectionMatrix, frame);
}


}
