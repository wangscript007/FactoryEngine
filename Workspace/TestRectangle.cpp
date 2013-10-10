
#include <Workspace/TestRectangle.h>

namespace ftr {

void TestRectangle::Render(Layer& layer)
{
    const float k = 0.5f;
    static const glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    rectanglePrimitive.mVec[0] = glm::vec3(k,k,k);
    rectanglePrimitive.mVec[1] = glm::vec3(-k,k,k);
    rectanglePrimitive.mVec[2] = glm::vec3(-k,-k,k);
    rectanglePrimitive.mVec[3] = glm::vec3(k,-k,k);
    rectanglePrimitive.color = color;
    layer.AddPrimitive(rectanglePrimitive);
}

}