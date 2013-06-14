
#pragma once

namespace ftr {

class ShadersInput
{
public:
    enum UniformCounts {
        kLightsCount = 2
    };
    
   
    
    struct Input {
        GLuint vertex;
        GLuint normal;
        GLuint color;
        GLuint transform;
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
        } light[kLightsCount];
    };
    
    struct Transform {
        Mat4 view;
        Mat4 projection;
        Mat4 rotation;
        Mat4 translation;
    };
    
    struct LightData {
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
        LightData() :
        spotExponent(1.0f),
        spotCutoff(0.0),
        spotCosCutoff(0.0),
        constantAttenuation(1.0),
        linearAttenuation(1.0),
        quadraticAttenuation(1.0) {}
    };
    
    
    ShadersInput(GLuint programId) : mProgramId(programId) {}
    virtual ~ShadersInput() {}
    void BindOutput();
    void Init();
    
    GLuint AttributeLocation(const std::string& name) const;
    GLuint UniformLocation(const std::string& name) const;
    GLuint BlockBuffer(const std::string& name) const;
    
    GLuint colorLocation() const { return mInput.color; }
    GLuint normalLocation() const { return mInput.normal; }
    GLuint vertexLocation() const { return mInput.vertex; }
    
    void InputTransform(const Transform& transform);
    void InputLight(const LightData& lightData);
    
private:
    GLuint mProgramId;
    Input mInput;
};
    
}

