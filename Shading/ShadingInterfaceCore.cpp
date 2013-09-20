
#include <Shading/ShadingInterfaceCore.h>

namespace ftr {
    

GLuint ShadingInterface::AttributeLocation(const std::string& name) const
{
    GLint location = glGetAttribLocation(mProgramId, name.c_str());
    assert(location != -1);
    return location;
}

GLuint ShadingInterface::UniformLocation(const std::string& name) const
{
    GLint location = glGetUniformLocation(mProgramId, name.c_str());
    assert(location != -1);
    return location;
}

void ShadingInterface::SetupForProgramWithName(const std::string& name)
{
    if (name == "main")
    {
        mInterface.vertex = AttributeLocation("position");
        mInterface.color = AttributeLocation("color");
        mInterface.normal = AttributeLocation("normal");
        mInterface.transform.view = UniformLocation("transformVar.view");
        mInterface.transform.projection = UniformLocation("transformVar.projection");        
        mInterface.settings.lightsCount = UniformLocation("settingsVar.lightsCount");
        mInterface.settings.debugLineWidth = UniformLocation("settingsVar.debugLineWidth");
        mInterface.settings.debugOn = UniformLocation("settingsVar.debugOn");
        mInterface.settings.debugFloatScale = UniformLocation("settingsVar.debugFloatScale");
        mInterface.windowSize = UniformLocation("windowSize");
        for (int i = 0; i < 2; i++) {
            std::stringstream streamLocation;
            streamLocation << "light"<< i << ".";
            std::string locationString = streamLocation.str();
            mInterface.light[i].ambient = UniformLocation(locationString + "ambient");
            mInterface.light[i].diffuse = UniformLocation(locationString + "diffuse");
            mInterface.light[i].specular = UniformLocation(locationString + "specular");
            mInterface.light[i].position = UniformLocation(locationString + "position");
            mInterface.light[i].halfVector = UniformLocation(locationString + "halfVector");
            mInterface.light[i].spotDirection = UniformLocation(locationString + "spotDirection");
            mInterface.light[i].spotExponent = UniformLocation(locationString + "spotExponent");
            mInterface.light[i].spotCutoff = UniformLocation(locationString + "spotCutoff");
            mInterface.light[i].spotCosCutoff = UniformLocation(locationString + "spotCosCutoff");
            mInterface.light[i].constantAttenuation = UniformLocation(locationString + "constantAttenuation");
            mInterface.light[i].linearAttenuation = UniformLocation(locationString + "linearAttenuation");
            mInterface.light[i].quadraticAttenuation = UniformLocation(locationString + "quadraticAttenuation");
            mInterface.light[i].useLocalCoordinates = UniformLocation(locationString + "useLocalCoordinates");
        }
    }
    
    else if (name == "color")
    {
        mInterface.vertex = AttributeLocation("position");
        mInterface.color = AttributeLocation("color");
        mInterface.transform.view = UniformLocation("transformVar.view");
        mInterface.transform.projection = UniformLocation("transformVar.projection");
    }
    
    else {
        assert(false);
    }
}

void ShadingInterface::BindOutput()
{
    glBindFragDataLocation(mProgramId, 0, "color");
}
    
GLuint ShadingInterface::BlockBuffer(const std::string& name) const
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
    
void ShadingInterface::InputSettings(const Settings& settings)
{
    glUniform1i(mInterface.settings.lightsCount, settings.lightsCount);
    glUniform1i(mInterface.settings.debugLineWidth, settings.debugLineWidth);
    glUniform1i(mInterface.settings.debugOn, settings.debugOn);
    glUniform1f(mInterface.settings.debugFloatScale, settings.debugFloatScale);
}
    
void ShadingInterface::InputTransform(const Transform& transform)
{
    const GLfloat* view         = reinterpret_cast<const GLfloat*>(&transform.view);
    const GLfloat* projection   = reinterpret_cast<const GLfloat*>(&transform.projection);
    glUniformMatrix4fv(mInterface.transform.view,  1, false, view);
    glUniformMatrix4fv(mInterface.transform.projection,  1, false, projection);
    InputSettings(mSettings);
}
    
void ShadingInterface::InputWindowSize(const Vec2& windowSize)
{
    glUniform2fv(mInterface.windowSize, 1, reinterpret_cast<const GLfloat*>(&windowSize));
}
    
void ShadingInterface::InputLight(const Light::Data& lightData)
{
    const Light::Data* lightDataArray = &lightData;
    for (int i = 0; i < mSettings.lightsCount; i++) {
        glUniform4fv(mInterface.light[i].ambient, 1, reinterpret_cast<const GLfloat*>(&lightDataArray[i].ambient));
        glUniform4fv(mInterface.light[i].diffuse, 1, reinterpret_cast<const GLfloat*>(&lightDataArray[i].diffuse));
        glUniform4fv(mInterface.light[i].specular, 1, reinterpret_cast<const GLfloat*>(&lightDataArray[i].specular));
        glUniform4fv(mInterface.light[i].position, 1, reinterpret_cast<const GLfloat*>(&lightDataArray[i].position));
        glUniform4fv(mInterface.light[i].halfVector, 1, reinterpret_cast<const GLfloat*>(&lightDataArray[i].halfVector));
        glUniform3fv(mInterface.light[i].spotDirection, 1, reinterpret_cast<const GLfloat*>(&lightDataArray[i].spotDirection));
        glUniform1f(mInterface.light[i].spotExponent, lightDataArray[i].spotExponent);
        glUniform1f(mInterface.light[i].spotCutoff, lightDataArray[i].spotCutoff);
        glUniform1f(mInterface.light[i].spotCosCutoff, lightDataArray[i].spotCosCutoff);
        glUniform1f(mInterface.light[i].constantAttenuation, lightDataArray[i].constantAttenuation);
        glUniform1f(mInterface.light[i].linearAttenuation, lightDataArray[i].linearAttenuation);
        glUniform1f(mInterface.light[i].quadraticAttenuation, lightDataArray[i].quadraticAttenuation);
        glUniform1i(mInterface.light[i].useLocalCoordinates, lightDataArray[i].useLocalCoordinates);
    }
}
    
    
}

