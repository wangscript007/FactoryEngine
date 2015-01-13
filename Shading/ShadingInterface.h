
#pragma once

#include <Lighting/Light.h>
#include <Shading/ShadingProgram.h>
#include <Scene/Viewport.h>

#define MAX_LIGHTS_COUNT 5

namespace ftr {
class ShadingInterface
{
public:
    
    enum {
        kVertexAttributeIndex,
        kNormalAttributeIndex,
        kColorAttributeIndex,
        kPickingColorAttributeIndex
    };
    
    struct Bond {
        GLuint vertex;
        GLuint normal;
        GLuint color;
        GLuint pickingColor;
        struct Transform {
            GLuint view;
            GLuint projection;
        } transform;
        struct Settings {
            GLuint lightsCount;
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
    
    struct Settings {
        int lightsCount;
        Settings() :
        lightsCount(2) {}
    };
    
    virtual ~ShadingInterface() {}
    void BindOutput(GLuint programId);
    void CreateInterfaceForProgram(ShadingProgram::Type type, GLuint programID);
    
    void ActvateBondForProgramType(ShadingProgram::Type type);
    
    GLuint AttributeLocation(const std::string& name, GLuint programID) const;
    GLuint UniformLocation(const std::string& name, GLuint programID) const;
    GLuint BlockBuffer(const std::string& name, GLuint programID) const;
    
    GLuint colorLocation() const { return mActiveBond->color; }
    GLuint normalLocation() const { return mActiveBond->normal; }
    GLuint vertexLocation() const { return mActiveBond->vertex; }
    
    void InputViewport(const Viewport& viewport);
    void InputSettings(const Settings& settings);
    void InputLight(const Light::Data& lightData);
    void InputWindowSize(const glm::vec2& windowSize);
        
    Settings mSettings;
private:
    typedef std::map<ShadingProgram::Type, Bond> BondsMap;
    static Bond BondForProgramType(ShadingProgram::Type type);
    
    Bond* mActiveBond;
    BondsMap mBondsMap;
    
};
    
}

