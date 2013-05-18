
#pragma once

#include <Lighting/LightingModel.h>

namespace ftr {

class LigthtingModelFactory
{
public:
    LigthtingModelFactory();
    virtual ~LigthtingModelFactory() {}

    LightingModel* CreateModelWithName(const std::string& modelName);
    
private:
    typedef std::function<LightingModel* ()> CreationFunction;
    typedef std::map<std::string, CreationFunction> FunctionsMap;
    
    FunctionsMap mFunctionsMap;
    
    static LightingModel* DefaultModel();
    
};
    
}

