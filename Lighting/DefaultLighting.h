
#pragma once

#include <Lighting/LightingModel.h>

namespace ftr {

class DefaultLighting : public LightingModel
{
public:
    DefaultLighting();
    virtual ~DefaultLighting();
    virtual void SetupLights();
    
private:
    Light* AddLightWithType(Light::Type type);
};
    
}

