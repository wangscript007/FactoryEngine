
#include <Lighting/LightingCollection.h>
#include <Lighting/DefaultLighting.h>
#include <Lighting/LigthtingModelFactory.h>

namespace ftr {
    
LightingCollection::LightingCollection()
{
    mActiveModel = mFactory.CreateModelWithName("default");
}
    
LightingCollection::~LightingCollection()
{
    FT_DELETE(mActiveModel);
}

}

