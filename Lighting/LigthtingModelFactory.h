
#pragma once

#include <Lighting/LightingModel.h>
#include <Shading/ShadersInput.h>

namespace ftr {

class LigthtingModelFactory
{
public:
    LigthtingModelFactory();
    virtual ~LigthtingModelFactory() {}
    
    LightingModel* CreateModelWithName(const std::string& modelName);
    
private:
    typedef std::function<LightingModel* ()> CreationMethod;
    typedef std::map<std::string, CreationMethod> MethodsMap;
    
    static LightingModel* DefaultModel();
    
    MethodsMap mMethodsMap;
    ShadersInput* mShadersInput;
};
    
}

