
#include <Shading/ShadingInterfaceCore.h>
#include <Main/GLError.h>

namespace ftr {
        
void ShadingInterface::ActvateBondForProgramType(ShadingProgram::Type type)
{
    mActiveBond = &mBondsMap[type];
}

void ShadingInterface::CreateInterfaceForProgram(ShadingProgram::Type type, GLuint programId)
{
    Bond& bond = mBondsMap[type];
    switch (type) {
        case ShadingProgram::kMain: {
            bond.transform.view = UniformLocation("transformVar.view", programId);
            bond.transform.projection = UniformLocation("transformVar.projection", programId);
            bond.settings.lightsCount = UniformLocation("settingsVar.lightsCount", programId);
            bond.settings.debugLineWidth = UniformLocation("settingsVar.debugLineWidth", programId);
            bond.settings.debugOn = UniformLocation("settingsVar.debugOn", programId);
            bond.settings.debugFloatScale = UniformLocation("settingsVar.debugFloatScale", programId);
            bond.windowSize = UniformLocation("windowSize", programId);
            for (int i = 0; i < 2; i++) {
                std::stringstream streamLocation;
                streamLocation << "light"<< i << ".";
                std::string locationString = streamLocation.str();
                bond.light[i].ambient = UniformLocation(locationString + "ambient", programId);
                bond.light[i].diffuse = UniformLocation(locationString + "diffuse", programId);
                bond.light[i].specular = UniformLocation(locationString + "specular", programId);
                bond.light[i].position = UniformLocation(locationString + "position", programId);
                bond.light[i].halfVector = UniformLocation(locationString + "halfVector", programId);
                bond.light[i].spotDirection = UniformLocation(locationString + "spotDirection", programId);
                bond.light[i].spotExponent = UniformLocation(locationString + "spotExponent", programId);
                bond.light[i].spotCutoff = UniformLocation(locationString + "spotCutoff", programId);
                bond.light[i].spotCosCutoff = UniformLocation(locationString + "spotCosCutoff", programId);
                bond.light[i].constantAttenuation = UniformLocation(locationString + "constantAttenuation", programId);
                bond.light[i].linearAttenuation = UniformLocation(locationString + "linearAttenuation", programId);
                bond.light[i].quadraticAttenuation = UniformLocation(locationString + "quadraticAttenuation", programId);
                bond.light[i].useLocalCoordinates = UniformLocation(locationString + "useLocalCoordinates", programId);
            }
        } break;
    
        case ShadingProgram::kColor: {
            bond.transform.view = UniformLocation("transformVar.view", programId);
            bond.transform.projection = UniformLocation("transformVar.projection", programId);
        } break;
            
        case ShadingProgram::kTest: {
            
        } break;
    
        default:
            assert(false);
            break;
    }
    bond.vertex         = kVertexAttributeIndex;
    bond.normal         = kNormalAttributeIndex;
    bond.color          = kColorAttributeIndex;
    bond.pickingColor   = kColorAttributeIndex;
    

}

void ShadingInterface::BindOutput(GLuint programId)
{
    glBindAttribLocation(programId, kVertexAttributeIndex, "position");
    glBindAttribLocation(programId, kNormalAttributeIndex, "normal");
    glBindAttribLocation(programId, kColorAttributeIndex, "color");
    glBindAttribLocation(programId, kPickingColorAttributeIndex, "pickingColor");
    glBindFragDataLocation(programId, 0, "outputF");
    
}
    
GLuint ShadingInterface::AttributeLocation(const std::string& name, GLuint programId) const
{
    GLint location = glGetAttribLocation(programId, name.c_str());
    assert(location != -1);
    return location;
}

GLuint ShadingInterface::UniformLocation(const std::string& name, GLuint programId) const
{
    GLint location = glGetUniformLocation(programId, name.c_str());
    assert(location != -1);
    return location;
}
    
GLuint ShadingInterface::BlockBuffer(const std::string& name, GLuint programId) const
{
    static GLuint bindingPoint = 1;
    GLuint buffer, blockIndex;
    blockIndex = glGetUniformBlockIndex(programId, name.c_str());
    assert(blockIndex != GL_INVALID_INDEX);
    glUniformBlockBinding(programId, blockIndex, bindingPoint);
    glGenBuffers(1, &buffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer);
    bindingPoint++;
    return buffer;
}
    
void ShadingInterface::InputSettings(const Settings& settings)
{
    glUniform1i(mActiveBond->settings.lightsCount, settings.lightsCount);
    glUniform1i(mActiveBond->settings.debugLineWidth, settings.debugLineWidth);
    glUniform1i(mActiveBond->settings.debugOn, settings.debugOn);
    glUniform1f(mActiveBond->settings.debugFloatScale, settings.debugFloatScale);
}
    
void ShadingInterface::InputViewport(const Viewport& viewport)
{
    glUniformMatrix4fv(mActiveBond->transform.view,  1, false, glm::value_ptr(viewport.modelviewMatrix));
    glUniformMatrix4fv(mActiveBond->transform.projection,  1, false, glm::value_ptr(viewport.projectionMatrix));
    InputSettings(mSettings);
}
    
void ShadingInterface::InputWindowSize(const glm::vec2& windowSize)
{
    glUniform2fv(mActiveBond->windowSize, 1, glm::value_ptr(windowSize));
}
    
void ShadingInterface::InputLight(const Light::Data& lightData)
{
    const Light::Data* lightDataArray = &lightData;
    for (int i = 0; i < mSettings.lightsCount; i++) {
        glUniform4fv(mActiveBond->light[i].ambient, 1, glm::value_ptr(lightDataArray[i].ambient));
        glUniform4fv(mActiveBond->light[i].diffuse, 1, glm::value_ptr(lightDataArray[i].diffuse));
        glUniform4fv(mActiveBond->light[i].specular, 1, glm::value_ptr(lightDataArray[i].specular));
        glUniform4fv(mActiveBond->light[i].position, 1, glm::value_ptr(lightDataArray[i].position));
        glUniform4fv(mActiveBond->light[i].halfVector, 1, glm::value_ptr(lightDataArray[i].halfVector));
        glUniform3fv(mActiveBond->light[i].spotDirection, 1, glm::value_ptr(lightDataArray[i].spotDirection));
        glUniform1f(mActiveBond->light[i].spotExponent, lightDataArray[i].spotExponent);
        glUniform1f(mActiveBond->light[i].spotCutoff, lightDataArray[i].spotCutoff);
        glUniform1f(mActiveBond->light[i].spotCosCutoff, lightDataArray[i].spotCosCutoff);
        glUniform1f(mActiveBond->light[i].constantAttenuation, lightDataArray[i].constantAttenuation);
        glUniform1f(mActiveBond->light[i].linearAttenuation, lightDataArray[i].linearAttenuation);
        glUniform1f(mActiveBond->light[i].quadraticAttenuation, lightDataArray[i].quadraticAttenuation);
        glUniform1i(mActiveBond->light[i].useLocalCoordinates, lightDataArray[i].useLocalCoordinates);
    }
}
    
    
    
}

