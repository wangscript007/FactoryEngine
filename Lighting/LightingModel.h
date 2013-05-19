
#pragma once

#include <Lighting/Light.h>

namespace ftr {

class ShadersInput;
    
class LightingModel
{
public:
    typedef std::vector<Light*> LightsVector;
    
    LightingModel();
    virtual ~LightingModel();
    
    virtual void SetupLights() = 0;
    
    void setShadersInput(ShadersInput* shadersInput) { mShadersInput = shadersInput; }
    
protected:
    LightsVector mLightsVector;
    ShadersInput* mShadersInput;
};
    
}

