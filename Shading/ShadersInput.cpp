
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
    mInput.color = AttributeLocation("color");
    mInput.projMatrix = UniformLocation("projMatrix");
    mInput.viewMatrix = UniformLocation("viewMatrix");
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

    
}

