
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
        Vec4 ambient;
        Vec4 diffuse;
        Vec4 specular;
        Vec4 position;
        Vec4 halfVector;
        Vec3 spotDirection;
        float spotExponent;
        float spotCutoff;
        float spotCosCutoff;
        float constantAttenuation;
        float linearAttenuation;
        float quadraticAttenuation;
        int useLocalCoordinates;
        Data() :
        spotExponent(1.0f),
        spotCutoff(0.0),
        spotCosCutoff(0.0),
        constantAttenuation(1.0),
        linearAttenuation(1.0),
        quadraticAttenuation(1.0),
        useLocalCoordinates(1) {}
    };
    
    Light(Type type);
    virtual ~Light() {}
    Data mData;
    
private:
    Type mType;
};

}

