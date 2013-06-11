
#include <Lighting/LightingModel.h>

namespace ftr {

LightingModel::LightingModel()
{
    
}

LightingModel::~LightingModel()
{
    
}
    
ShadersInput::LightData* LightingModel::Data() const
{
    assert(mLightsVector.size() <= ShadersInput::kLightsCount);
    ShadersInput::LightData* data = reinterpret_cast<ShadersInput::LightData*>(new char[ModelDataSize()]);
    for (int i = 0; i < mLightsVector.size(); ++i) {
        data[i] = mLightsVector[i]->data();
    }
    for (size_t i = mLightsVector.size(); i < ShadersInput::kLightsCount; ++i) {
        data[i] = ShadersInput::LightData();
    }
    return data;
}
    
size_t LightingModel::ModelDataSize() const
{
    return sizeof(ShadersInput::LightData) * ShadersInput::kLightsCount;
}
        
}

