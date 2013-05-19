
#include "DefaultLighting.h"

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
    light->lightData().position = Vec4(-5.0f, -5.0f, -5.0f, 1.0f);
    light->lightData().intensity = 1.0f;
    
    mShadersInput->InputLight(light->lightData());
}
    
Light* DefaultLighting::AddLightWithType(Light::Type type)
{
    Light* light = new Light(type);
    mLightsVector.push_back(light);
    return light;
}
    
}
