
#pragma once

#include <Shading/ShadingInterface.h>
#include <Lighting/Light.h>


namespace ftr {

class ShadingInterface;
    
class LightingModel
{
public:
    typedef std::vector<Light*> LightsVector;
    
    LightingModel();
    virtual ~LightingModel();
    
    virtual void SetupLights() = 0;
    
    void setShadingInterface(ShadingInterface* ShadingInterface) { mShadingInterface = ShadingInterface; }
    void SendDataToShader();
protected:
    LightsVector mLightsVector;
    ShadingInterface* mShadingInterface;
    
private:
    size_t ModelDataSize() const;
    Light::Data* Data() const;
    
};
    
}

