
#pragma once

namespace ftr {

class ShadersInput
{
public:
    static const int kLightsCount;
    
    struct Input {
        GLuint vertex;
        GLuint normal;
        GLuint color;
        GLuint transform;
        GLuint light;
    };
    
    struct Transform {
        Mat4 view;
        Mat4 projection;
        Mat4 rotation;
        Mat4 translation;
    };
    
    struct LightData {
        Vec4 ambient;               // Aclarri
        Vec4 diffuse;               // Dcli
        Vec4 specular;              // Scli
        Vec4 position;              // Ppli
        Vec4 halfVector;            // Derived: Hi
        Vec3 spotDirection;         // Sdli
        float spotExponent;         // Srli
        float spotCutoff;           // Crli
                                    // (range: [0.0,90.0], 180.0)
        float spotCosCutoff;        // Derived: cos(Crli)
                                    // (range: [1.0,0.0],-1.0)
        float constantAttenuation;  // K0
        float linearAttenuation;    // K1
        float quadraticAttenuation; // K2
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

