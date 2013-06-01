
#include <Shading/ShadersInputES.h>

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
    mInput.transform.view = UniformLocation("transformVar.view");
    mInput.transform.projection = UniformLocation("transformVar.projection");
    mInput.transform.rotation = UniformLocation("transformVar.rotation");
    mInput.transform.translation = UniformLocation("transformVar.translation");
}
    
void ShadersInput::InputTransform(const Transform& transform)
{
    const GLfloat* view = reinterpret_cast<const GLfloat*>(&transform.view);
    const GLfloat* projection = reinterpret_cast<const GLfloat*>(&transform.projection);
    const GLfloat* rotation = reinterpret_cast<const GLfloat*>(&transform.rotation);
    const GLfloat* translation = reinterpret_cast<const GLfloat*>(&transform.translation);
    glUniformMatrix4fv(mInput.transform.view,  1, false, view);
    glUniformMatrix4fv(mInput.transform.projection,  1, false, projection);
    glUniformMatrix4fv(mInput.transform.rotation,  1, false, rotation);
    glUniformMatrix4fv(mInput.transform.translation,  1, false, translation);
}
    
void ShadersInput::InputLight(const LightData& lightData)
{
    
}
    
void ShadersInput::BindOutput()
{
    
}

    
}

