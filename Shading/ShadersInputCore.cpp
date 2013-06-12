
#include <Shading/ShadersInputCore.h>

namespace ftr {
    
const int ShadersInput::kLightsCount = 5;

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
    mInput.light = BlockBuffer("Light[0]");
    mInput.transform = BlockBuffer("Transform");
    
}

void ShadersInput::BindOutput()
{
    glBindFragDataLocation(mProgramId, 0, "outputF");
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
    
void ShadersInput::InputTransform(const Transform& transform)
{
    glBindBuffer(GL_UNIFORM_BUFFER, mInput.transform);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Transform), &transform, GL_DYNAMIC_DRAW);
}
    
void ShadersInput::InputLight(const LightData& lightData)
{
    glBindBuffer(GL_UNIFORM_BUFFER, mInput.light);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightData)*kLightsCount, &lightData, GL_DYNAMIC_DRAW);
}
    
}

