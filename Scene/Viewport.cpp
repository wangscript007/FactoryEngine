
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
    
glm::vec3 Viewport::SceneCoordsAtCenter() const
{
    return SceneCoordsAt(glm::vec2(frame[2]/2, frame[3]/2));
}
    
Segment Viewport::RayAtPoint(const glm::vec2& point) const
{
    return Segment(UnProject(glm::vec3(point.x, point.y, 0.0f)),
                   UnProject(glm::vec3(point.x, point.y, 1.0f)));
}
    
    
Triangle Viewport::Plane() const
{
    glm::vec2 vp[3];
    vp[0] = glm::vec2(0.0f, 0.0f);
    vp[1] = glm::vec2(frame[2], 0.0f);
    vp[2] = glm::vec2(frame[2], frame[3]);
    
    glm::vec3 cp[3];
    cp[0] = UnProject(glm::vec3(vp[0].x, vp[0].y, 0.0f));
    cp[1] = UnProject(glm::vec3(vp[1].x, vp[1].y, 0.0f));
    cp[2] = UnProject(glm::vec3(vp[2].x, vp[2].y, 0.0f));
    
    return Triangle(cp[0], cp[1], cp[2]);
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
