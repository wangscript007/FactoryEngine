
#pragma once

namespace ftr {

class ShadersInput
{
public:
    struct Input {
        GLuint vertex;
        GLuint normal;
        GLuint color;
        GLuint transform;
    };
    
    struct Transform {
        Mat4 view;
        Mat4 projection;
        Mat4 rotation;
        Mat4 translation;
    };
    
    ShadersInput(GLuint programId) : mProgramId(programId) {}
    virtual ~ShadersInput() {}
    void BindOutput();
    void Init();
    
    GLuint AttributeLocation(const std::string& name) const;
    GLuint UniformLocation(const std::string& name) const;
    GLuint BlockBuffer(const std::string& name);
    
    GLuint colorLocation() const { return mInput.color; }
    GLuint normalLocation() const { return mInput.normal; }
    GLuint vertexLocation() const { return mInput.vertex; }
    
    void InputTransform(const Transform& transform);
    
private:
    
    GLuint mProgramId;
    Input mInput;
};
    
}

