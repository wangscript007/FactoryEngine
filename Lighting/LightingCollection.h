
#pragma once

#include <Lighting/LigthtingModelFactory.h>

namespace ftr {

class LightingCollection
{
public:
    std::map<std::string, LightingModel*> ModelsMap;
    
    LightingCollection();
    virtual ~LightingCollection();
    
    LightingModel* activeModel() const { return mActiveModel; }
    
private:
    LigthtingModelFactory mFactory;
    LightingModel* mActiveModel;
};

}

