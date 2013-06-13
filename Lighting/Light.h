
#pragma once

#include <Shading/ShadersInput.h>

namespace ftr {

class Light
{
public:
    enum Type {
        kLightAmbient,
        kLightDirectional,
        kLightPoint,
        kLightSpot
    };
    
    
    Light(Type type);
    virtual ~Light() {}
    ShadersInput::LightData mData;
    
private:
    Type mType;
};

}

