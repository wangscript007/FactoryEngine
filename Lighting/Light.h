
#pragma once

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
    
    struct Data {
        Vec4 position;
        float intensity;
    };
    
    
    
    virtual ~Light() {}
    
private:
    Data mData;
};

}

