
#pragma once

#include <Lighting/LigthtingModelFactory.h>

namespace ftr {

class LightingCollection
{
public:
    std::map<std::string, LightingModel*> ModelsMap;
    
    LightingCollection();
    virtual ~LightingCollection();
    
private:
    LigthtingModelFactory mFactory;
    
    LightingModel* mActiveModel;
};

}

