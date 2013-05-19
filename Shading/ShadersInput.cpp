
#include <Shading/ShadersInput.h>

namespace ftr {

GLuint ShadersInput::AttributeLocation(const std::string& name) const
{
    GLint location = glGetAttribLocation(mProgramId, name.c_str());
    assert(location != -1);
    return location;
}

GLuint ShadersInput::UniformLocation(const std::string& name) const
{
    GLint location = glGetUniformLocation(mProgramId, name.c_str());
    assert(location != -1);
    return location;
}

void ShadersInput::Init()
{
    mInput.vertex = AttributeLocation("position");
    mInput.normal = AttributeLocation("normal");
    mInput.color = AttributeLocation("color");
    mInput.transform = BlockBuffer("Transform");
    //mInput.light = BlockBuffer("Light");
}
    
GLuint ShadersInput::BlockBuffer(const std::string& name) const
{
    GLuint bindingPoint = 1, buffer, blockIndex;
    blockIndex = glGetUniformBlockIndex(mProgramId, name.c_str());
    assert(blockIndex != GL_INVALID_INDEX);
    glUniformBlockBinding(mProgramId, blockIndex, bindingPoint);
    glGenBuffers(1, &buffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer);
    return buffer;
}

void ShadersInput::BindOutput()
{
    glBindFragDataLocation(mProgramId, 0, "outputF");
}
    
void ShadersInput::InputTransform(const Transform& transform)
{
    glBindBuffer(GL_UNIFORM_BUFFER, mInput.transform);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Transform), &transform, GL_DYNAMIC_DRAW);
}
    
void ShadersInput::InputLight(const LightData& lightData)
{
    return;
    glBindBuffer(GL_UNIFORM_BUFFER, mInput.light);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightData), &lightData, GL_DYNAMIC_DRAW);
}



    
}

