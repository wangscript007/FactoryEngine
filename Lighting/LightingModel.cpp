
#include <Lighting/LightingModel.h>

namespace ftr {

LightingModel::LightingModel()
    :mData(NULL)
{
    
}

LightingModel::~LightingModel()
{
    delete[] mData;
    mData = NULL;
}
    
Light::Data* LightingModel::Data()
{
    if (!mData) {
        assert(mLightsVector.size() <= mShadingInterface->mSettings.lightsCount);
        mData = reinterpret_cast<Light::Data*>(new char[ModelDataSize()]);
        for (int i = 0; i < mLightsVector.size(); ++i) {
            mData[i] = mLightsVector[i]->mData;
        }
        for (size_t i = mLightsVector.size(); i < mShadingInterface->mSettings.lightsCount; ++i) {
            mData[i] = Light::Data();
        }
    }
    return mData;
}
    
size_t LightingModel::ModelDataSize() const
{
    return sizeof(Light::Data) * mShadingInterface->mSettings.lightsCount;
}
    
void LightingModel::SendDataToShader()
{
    mShadingInterface->mSettings.lightsCount = static_cast<int>(mLightsVector.size());
    mShadingInterface->InputLight(*Data());
}
    
}

