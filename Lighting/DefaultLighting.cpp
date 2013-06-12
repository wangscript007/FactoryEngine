
#include <Lighting/DefaultLighting.h>

namespace ftr {
    
DefaultLighting::DefaultLighting()
{
    
}
    
DefaultLighting::~DefaultLighting()
{
    for(Light* light : mLightsVector) {
        FT_DELETE(light);
    }
    mLightsVector.clear();
}
    
void DefaultLighting::SetupLights()
{
    Light* light = AddLightWithType(Light::kLightDirectional);
    light->data().position = Vec4(-5.0f, -5.0f, -5.0f, 1.0f);
}
    
Light* DefaultLighting::AddLightWithType(Light::Type type)
{
    Light* light = new Light(type);
    mLightsVector.push_back(light);
    return light;
}
    
}
