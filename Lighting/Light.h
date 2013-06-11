
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
    
    ShadersInput::LightData& data() { return mData; }
    
private:
    ShadersInput::LightData mData;
    Type mType;
};

}

