
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

//    Light* pointLight = AddLightWithType(Light::kLightPoint);
//    pointLight->mData.position = glm::vec4(0.0f, 50.0f, 0.0f, 1.0f);
//    pointLight->mData.specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    pointLight->mData.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    pointLight->mData.ambient = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    pointLight->mData.quadraticAttenuation = 0.001;
//    pointLight->mData.linearAttenuation = 0.1;
//    pointLight->mData.constantAttenuation = 0.01;
//    pointLight->mData.spotCutoff = 180.0;
//    pointLight->mData.spotExponent = 2;
//    pointLight->mData.spotCosCutoff = 0.01;
//    pointLight->mData.spotDirection = glm::vec3(0.0, -1.0, 0.0);
//    pointLight->mData.useLocalCoordinates = 1;

    
    
//    Light* spotLight = AddLightWithType(Light::kLightSpot);
//    spotLight->mData.position = glm::vec4(0.0f, 20.0f, 0.0f, 1.0f);
//    spotLight->mData.specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    spotLight->mData.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    spotLight->mData.ambient = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    spotLight->mData.quadraticAttenuation = 0.001;
//    spotLight->mData.linearAttenuation = 0.1;
//    spotLight->mData.constantAttenuation = 0.01;
//    spotLight->mData.spotCutoff = 20.0;
//    spotLight->mData.spotExponent = 1;
//    spotLight->mData.spotCosCutoff = 0.01;
//    spotLight->mData.spotDirection = glm::vec3(0.0, -1.0, 0.0);
//    spotLight->mData.useLocalCoordinates = 1;
    
    
    Light* directionalLight = AddLightWithType(Light::kLightDirectional);
    directionalLight->mData.position = glm::vec4(0.0, 0.0, 1.0, 0.0);
    directionalLight->mData.diffuse = glm::vec4(1.0, 1.0, 1.0, 1.0);
    directionalLight->mData.useLocalCoordinates = 0;
}
    
Light* DefaultLighting::AddLightWithType(Light::Type type)
{
    Light* light = new Light(type);
    mLightsVector.push_back(light);
    return light;
}
    
}
