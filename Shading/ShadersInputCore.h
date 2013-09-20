
#pragma once

#include <Lighting/Light.h>

#define MAX_LIGHTS_COUNT 5

namespace ftr {
class ShadersInput
{
public:
    
    struct Input {
        GLuint vertex;
        GLuint normal;
        GLuint color;
        struct Transform {
            GLuint view;
            GLuint projection;
        } transform;
        
        struct Settings {
            GLuint lightsCount;
            GLuint debugLineWidth;
            GLuint debugOn;
            GLuint debugFloatScale;
        } settings;
        GLuint windowSize;
        struct Light {
            GLuint ambient;
            GLuint diffuse;
            GLuint specular;
            GLuint position;
            GLuint halfVector;
            GLuint spotDirection;
            GLuint spotExponent;
            GLuint spotCutoff;
            GLuint spotCosCutoff;
            GLuint constantAttenuation;
            GLuint linearAttenuation;
            GLuint quadraticAttenuation;
            GLuint useLocalCoordinates;
        } light[MAX_LIGHTS_COUNT];
    };
    
    struct Transform {
        Mat4 view;
        Mat4 projection;
    };
    
    
    struct Settings {
        int lightsCount;
        int debugLineWidth;
        int debugOn;
        float debugFloatScale;
        Settings() :
        lightsCount(2),
        debugOn(0),
        debugLineWidth(2.0f),
        debugFloatScale(1.0f) {}
    };
    
    ShadersInput(GLuint programId) : mProgramId(programId) {}
    virtual ~ShadersInput() {}
    void BindOutput();
    void SetupForProgramWithName(const std::string& mName);
    
    GLuint AttributeLocation(const std::string& name) const;
    GLuint UniformLocation(const std::string& name) const;
    GLuint BlockBuffer(const std::string& name) const;
    
    GLuint colorLocation() const { return mInput.color; }
    GLuint normalLocation() const { return mInput.normal; }
    GLuint vertexLocation() const { return mInput.vertex; }
    
    void InputTransform(const Transform& transform);
    void InputSettings(const Settings& settings);
    void InputLight(const Light::Data& lightData);
    void InputWindowSize(const Vec2& windowSize);
        
    Settings mSettings;
private:
    GLuint mProgramId;
    Input mInput;
    
};
    
}

