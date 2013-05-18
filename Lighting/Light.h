
#pragma once

class Light
{
public:
    enum Type {
        kLightAmbient,
        kLightDirectional,
        kLightPoint,
        kLightSpot
    };
    
    virtual ~Light() {}
    
private:
    
    
};

