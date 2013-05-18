
#pragma once

#include <Lighting/Light.h>

namespace ftr {

class LightingModel
{
public:
    typedef std::vector<Light*> LightsVector;
    
    LightingModel();
    virtual ~LightingModel();
    
private:
    LightsVector mLightsVector;
};
    
}

