
#pragma once

#include <Shading/ShadersInput.h>
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
    void SendDataToShader();
protected:
    LightsVector mLightsVector;
    ShadersInput* mShadersInput;
    
private:
    size_t ModelDataSize() const;
    Light::Data* Data() const;
    
};
    
}

