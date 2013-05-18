
#pragma once

#include <Lighting/Light.h>

class LightingModel
{
public:
    typedef std::vector<Light*> LightsVector;
    
    LightingModel();
    virtual ~LightingModel();
    
private:
    LightsVector mLightsVector;
};

