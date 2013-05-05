
#include <Workspace/TestRectangle.h>

namespace ftr {

void TestRectangle::Render(Layer& layer)
{
    const float k = 1;
    static const Color4f color = Color4f(0.0f, 1.0f, 0.0f, 1.0f);
    rectanglePrimitive.mVec[0].set(k,k,k);
    rectanglePrimitive.mVec[1].set(-k,k,k);
    rectanglePrimitive.mVec[2].set(-k,-k,k);
    rectanglePrimitive.mVec[3].set(k,-k,k);
    rectanglePrimitive.color = color;
    layer.AddPrimitive(rectanglePrimitive);
}

}