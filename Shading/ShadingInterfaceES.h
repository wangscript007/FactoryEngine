
#pragma once

namespace ftr {

class ShadingInterface
{
public:
    struct Input {
        struct Transform {
            GLuint view;
            GLuint projection;
            GLuint rotation;
            GLuint translation;
        } transform;
        GLuint vertex;
        GLuint normal;
        GLuint color;
        GLuint light;
    };
    
    struct Transform {
        glm::mat4 view;
        glm::mat4 projection;
        glm::mat4 rotation;
        glm::mat4 translation;
    };
    
    struct LightData {
        glm::vec4 position;
        float intensity;
    };
    
    ShadingInterface(GLuint programId) : mProgramId(programId) {}
    virtual ~ShadingInterface() {}
    void BindOutput();
    void Init();
    
    GLuint AttributeLocation(const std::string& name) const;
    GLuint UniformLocation(const std::string& name) const;
    
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

