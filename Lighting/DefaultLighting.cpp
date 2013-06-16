
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
    spotLight->mData.position = Vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spotLight->mData.ambient = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
    spotLight->mData.diffuse = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
    spotLight->mData.specular = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
    spotLight->mData.quadraticAttenuation = 0.05;
    spotLight->mData.linearAttenuation = 0.01;
    spotLight->mData.constantAttenuation = 0.01;
    spotLight->mData.spotCutoff = 180.0;
    spotLight->mData.spotCosCutoff = .0;
    spotLight->mData.spotDirection = Vec3(1.0, 1.0, 0.0);
    spotLight->mData.useLocalCoordinates = 1;
    
    Light* directionalLight = AddLightWithType(Light::kLightDirectional);
    directionalLight->mData.diffuse = Vec4(1.0, 1.0, 1.0, 0.0);
    directionalLight->mData.position = Vec4(0.0, 0.0, 1.0, 0.0);
    directionalLight->mData.useLocalCoordinates = 1;
    
//    Light* spotLight = AddLightWithType(Light::kLightPoint);
//    spotLight->mData.position = Vec4(5.0f, 5.0f, 5.0f, 1.0f);
//    spotLight->mData.ambient = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    spotLight->mData.diffuse = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    spotLight->mData.specular = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    spotLight->mData.quadraticAttenuation = 0.05;
//    spotLight->mData.linearAttenuation = 0.01;
//    spotLight->mData.constantAttenuation = 0.01;
//    spotLight->mData.spotCutoff = 180.0;
//    spotLight->mData.spotCosCutoff = .0;
//    spotLight->mData.spotDirection = Vec3(1.0, 1.0, 0.0);
//    spotLight->mData.useLocalCoordinates = 1;


}
    
Light* DefaultLighting::AddLightWithType(Light::Type type)
{
    Light* light = new Light(type);
    mLightsVector.push_back(light);
    return light;
}
    
}
