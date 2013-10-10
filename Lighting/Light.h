
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
        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec4 position;
        glm::vec4 halfVector;
        glm::vec3 spotDirection;
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

