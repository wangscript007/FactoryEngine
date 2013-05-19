
#include <Lighting/LigthtingModelFactory.h>
#include <Lighting/DefaultLighting.h>

namespace ftr {
    
LigthtingModelFactory::LigthtingModelFactory()
{
    mMethodsMap["default"] = LigthtingModelFactory::DefaultModel;
}
    
LightingModel* LigthtingModelFactory::CreateModelWithName(const std::string& modelName)
{
   return mMethodsMap[modelName]();
}

LightingModel* LigthtingModelFactory::DefaultModel()
{
    return new DefaultLighting();
}
    
}