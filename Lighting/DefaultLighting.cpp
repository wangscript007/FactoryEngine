
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
    Light* directionalLight = AddLightWithType(Light::kLightDirectional);
    directionalLight->mData.diffuse = Vec4(1.0, 1.0, 1.0, 1.0);
    directionalLight->mData.position = Vec4(0.0, 0.0, 1.0, 0.0);
    /*
    Light* directionalLight = AddLightWithType(Light::kLightDirectional);
    directionalLight->mData.diffuse = Vec4(0.0, 1.0, 0.0, 1.0);
    directionalLight->mData.position = Vec4(5.0f, 5.0f, 5.0f, 0.0f);
    */
}
    
Light* DefaultLighting::AddLightWithType(Light::Type type)
{
    Light* light = new Light(type);
    mLightsVector.push_back(light);
    return light;
}
    
}
