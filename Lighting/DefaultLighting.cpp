
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
    Light* spotLight = AddLightWithType(Light::kLightPoint);
    spotLight->mData.position = Vec4(4.0f, 2.0f, 4.0f, 1.0f);
    spotLight->mData.ambient = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
    spotLight->mData.quadraticAttenuation = 1.0;
    spotLight->mData.linearAttenuation = 1.0;
    spotLight->mData.constantAttenuation = 0.0;
    spotLight->mData.spotExponent = 20.0;
    spotLight->mData.spotCosCutoff = 100.0;
    spotLight->mData.spotDirection = Vec3(0.0, -1.0, 0.0);
    
    Light* directionalLight = AddLightWithType(Light::kLightDirectional);
    directionalLight->mData.diffuse = Vec4(1.0, 1.0, 1.0, 0.0);
    directionalLight->mData.position = Vec4(0.0, 0.0, 1.0, 0.0);
}
    
Light* DefaultLighting::AddLightWithType(Light::Type type)
{
    Light* light = new Light(type);
    mLightsVector.push_back(light);
    return light;
}
    
}
