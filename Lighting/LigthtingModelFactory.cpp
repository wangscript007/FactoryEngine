
#include <Lighting/LigthtingModelFactory.h>
#include <Lighting/DefaultLighting.h>

namespace ftr {
    
LigthtingModelFactory::LigthtingModelFactory()
{
    mFunctionsMap["default"] = LigthtingModelFactory::DefaultModel;
}
    
LightingModel* LigthtingModelFactory::CreateModelWithName(const std::string& modelName)
{
   return mFunctionsMap[modelName]();
}

LightingModel* LigthtingModelFactory::DefaultModel()
{
    return new DefaultLighting();
}
    
}