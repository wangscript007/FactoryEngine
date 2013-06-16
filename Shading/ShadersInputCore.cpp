
#include <Shading/ShadersInputCore.h>

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
    mInput.settings = BlockBuffer("Settings");
    mInput.windowSize = UniformLocation("windowSize");
    for (int i = 0; i < 2; i++) {
        std::stringstream streamLocation;
        streamLocation << "light"<< i << ".";
        std::string locationString = streamLocation.str();
        mInput.light[i].ambient = UniformLocation(locationString + "ambient");
        mInput.light[i].diffuse = UniformLocation(locationString + "diffuse");
        mInput.light[i].specular = UniformLocation(locationString + "specular");
        mInput.light[i].position = UniformLocation(locationString + "position");
        mInput.light[i].halfVector = UniformLocation(locationString + "halfVector");
        mInput.light[i].spotDirection = UniformLocation(locationString + "spotDirection");
        mInput.light[i].spotExponent = UniformLocation(locationString + "spotExponent");
        mInput.light[i].spotCutoff = UniformLocation(locationString + "spotCutoff");
        mInput.light[i].spotCosCutoff = UniformLocation(locationString + "spotCosCutoff");
        mInput.light[i].constantAttenuation = UniformLocation(locationString + "constantAttenuation");
        mInput.light[i].linearAttenuation = UniformLocation(locationString + "linearAttenuation");
        mInput.light[i].quadraticAttenuation = UniformLocation(locationString + "quadraticAttenuation");
        mInput.light[i].useLocalCoordinates = UniformLocation(locationString + "useLocalCoordinates");
    }
    InputSettings(mSettings);
    
}

void ShadersInput::BindOutput()
{
    glBindFragDataLocation(mProgramId, 0, "outputF");
}
    
GLuint ShadersInput::BlockBuffer(const std::string& name) const
{
    static GLuint bindingPoint = 1;
    GLuint buffer, blockIndex;
    blockIndex = glGetUniformBlockIndex(mProgramId, name.c_str());
    assert(blockIndex != GL_INVALID_INDEX);
    glUniformBlockBinding(mProgramId, blockIndex, bindingPoint);
    glGenBuffers(1, &buffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer);
    bindingPoint++;
    return buffer;
}
    
void ShadersInput::InputSettings(const Settings& settings)
{
    glBindBuffer(GL_UNIFORM_BUFFER, mInput.settings);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Settings), &settings, GL_DYNAMIC_DRAW);
}
    
void ShadersInput::InputTransform(const Transform& transform)
{
    glBindBuffer(GL_UNIFORM_BUFFER, mInput.transform);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Transform), &transform, GL_DYNAMIC_DRAW);
    InputSettings(mSettings);
}
    
void ShadersInput::InputWindowSize(const Vec2& windowSize)
{
    glUniform2fv(mInput.windowSize, 1, reinterpret_cast<const GLfloat*>(&windowSize));
}
    
void ShadersInput::InputLight(const Light::Data& lightData)
{
    const Light::Data* lightDataArray = &lightData;
    for (int i = 0; i < mSettings.lightsCount; i++) {
        glUniform4fv(mInput.light[i].ambient, 1, reinterpret_cast<const GLfloat*>(&lightDataArray[i].ambient));
        glUniform4fv(mInput.light[i].diffuse, 1, reinterpret_cast<const GLfloat*>(&lightDataArray[i].diffuse));
        glUniform4fv(mInput.light[i].specular, 1, reinterpret_cast<const GLfloat*>(&lightDataArray[i].specular));
        glUniform4fv(mInput.light[i].position, 1, reinterpret_cast<const GLfloat*>(&lightDataArray[i].position));
        glUniform4fv(mInput.light[i].halfVector, 1, reinterpret_cast<const GLfloat*>(&lightDataArray[i].halfVector));
        glUniform3fv(mInput.light[i].spotDirection, 1, reinterpret_cast<const GLfloat*>(&lightDataArray[i].spotDirection));
        glUniform1f(mInput.light[i].spotExponent, lightDataArray[i].spotExponent);
        glUniform1f(mInput.light[i].spotCutoff, lightDataArray[i].spotCutoff);
        glUniform1f(mInput.light[i].spotCosCutoff, lightDataArray[i].spotCosCutoff);
        glUniform1f(mInput.light[i].constantAttenuation, lightDataArray[i].constantAttenuation);
        glUniform1f(mInput.light[i].linearAttenuation, lightDataArray[i].linearAttenuation);
        glUniform1f(mInput.light[i].quadraticAttenuation, lightDataArray[i].quadraticAttenuation);
        glUniform1i(mInput.light[i].useLocalCoordinates, lightDataArray[i].useLocalCoordinates);
    }
}
    
    
}

