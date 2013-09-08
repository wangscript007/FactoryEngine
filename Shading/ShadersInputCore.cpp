
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
    mInput.color = AttributeLocation("color");
    mInput.normal = AttributeLocation("normal");
#ifndef RECTANGLE_TEST
#ifdef USE_BLOCK_BUFFER
    mInput.transform = BlockBuffer("Transform");
    mInput.settings = BlockBuffer("Settings");
#else
    mInput.transform.view = UniformLocation("transformVar.view");
    mInput.transform.projection = UniformLocation("transformVar.projection");
    mInput.transform.rotation = UniformLocation("transformVar.rotation");
    mInput.transform.translation = UniformLocation("transformVar.translation");
    
    mInput.settings.lightsCount = UniformLocation("settingsVar.lightsCount");
    mInput.settings.debugLineWidth = UniformLocation("settingsVar.debugLineWidth");
    mInput.settings.debugOn = UniformLocation("settingsVar.debugOn");
    mInput.settings.debugFloatScale = UniformLocation("settingsVar.debugFloatScale");
#endif
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
#endif
}

void ShadersInput::BindOutput()
{
    glBindFragDataLocation(mProgramId, 0, "color");
}
    
GLuint ShadersInput::BlockBuffer(const std::string& name) const
{
#ifndef USE_BLOCK_BUFFER
    return 0;
#endif
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
#ifdef USE_BLOCK_BUFFER
    glBindBuffer(GL_UNIFORM_BUFFER, mInput.settings);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Settings), &settings, GL_DYNAMIC_DRAW);
#else
    glUniform1i(mInput.settings.lightsCount, settings.lightsCount);
    glUniform1i(mInput.settings.debugLineWidth, settings.debugLineWidth);
    glUniform1i(mInput.settings.debugOn, settings.debugOn);
    glUniform1f(mInput.settings.debugFloatScale, settings.debugFloatScale);
#endif
}
    
void ShadersInput::InputTransform(const Transform& transform)
{
#ifdef RECTANGLE_TEST
    return;
#endif
#ifdef USE_BLOCK_BUFFER
    glBindBuffer(GL_UNIFORM_BUFFER, mInput.transform);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Transform), &transform, GL_DYNAMIC_DRAW);
#else
    const GLfloat* view         = reinterpret_cast<const GLfloat*>(&transform.view);
    const GLfloat* projection   = reinterpret_cast<const GLfloat*>(&transform.projection);
    const GLfloat* rotation     = reinterpret_cast<const GLfloat*>(&transform.rotation);
    const GLfloat* translation  = reinterpret_cast<const GLfloat*>(&transform.translation);
    glUniformMatrix4fv(mInput.transform.view,  1, false, view);
    glUniformMatrix4fv(mInput.transform.projection,  1, false, projection);
    glUniformMatrix4fv(mInput.transform.rotation,  1, false, rotation);
    glUniformMatrix4fv(mInput.transform.translation,  1, false, translation);
    InputSettings(mSettings);
#endif
 
}
    
void ShadersInput::InputWindowSize(const Vec2& windowSize)
{
#ifdef RECTANGLE_TEST
    return;
#endif

    glUniform2fv(mInput.windowSize, 1, reinterpret_cast<const GLfloat*>(&windowSize));
}
    
void ShadersInput::InputLight(const Light::Data& lightData)
{
#ifdef RECTANGLE_TEST
    return;
#endif

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

