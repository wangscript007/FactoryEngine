
#include <Shading/ShadersInput.h>

namespace ftr {

GLuint ShadersInput::AttributeLocation(const std::string& name) const
{
    return glGetAttribLocation(mProgramId, name.c_str());
}

GLuint ShadersInput::UniformLocation(const std::string& name) const
{
    return glGetUniformLocation(mProgramId, name.c_str());
}

void ShadersInput::Init()
{
    mInput.vertex = AttributeLocation("position");
    mInput.normal = AttributeLocation("normal");
    mInput.color = AttributeLocation("color");
    mInput.projMatrix = UniformLocation("projMatrix");
    mInput.viewMatrix = UniformLocation("viewMatrix");
    mInput.rotationMatrix = UniformLocation("rotationMatrix");
    mInput.translationMatrix = UniformLocation("translationMatrix");
}

void ShadersInput::BindOutput()
{
    glBindFragDataLocation(mProgramId, 0, "outputF");
}
    
void ShadersInput::InputProjectionMatrix(Mat4* matrix)
{
    GLfloat* m = reinterpret_cast<GLfloat*>(matrix);
    glUniformMatrix4fv(mInput.projMatrix,  1, false, m);
}
    
void ShadersInput::InputViewMatrix(Mat4* matrix)
{
    GLfloat* m = reinterpret_cast<GLfloat*>(matrix);
    glUniformMatrix4fv(mInput.viewMatrix,  1, false, m);
}
    
void ShadersInput::InputRotationMatrix(Mat4* matrix)
{
    GLfloat* m = reinterpret_cast<GLfloat*>(matrix);
    glUniformMatrix4fv(mInput.rotationMatrix,  1, false, m);
}
    
void ShadersInput::InputTranslationMatrix(Mat4* matrix)
{
    GLfloat* m = reinterpret_cast<GLfloat*>(matrix);
    glUniformMatrix4fv(mInput.translationMatrix,  1, false, m);
}



    
}

