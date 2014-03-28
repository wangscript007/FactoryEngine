
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
#ifndef GLES
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
#endif
}
    
size_t LightingModel::ModelDataSize() const
{
#ifndef GLES
    return sizeof(Light::Data) * mShadingInterface->mSettings.lightsCount;
#endif
}
    
void LightingModel::SendDataToShader()
{
#ifndef GLES
    mShadingInterface->mSettings.lightsCount = static_cast<int>(mLightsVector.size());
    mShadingInterface->InputLight(*Data());
#endif
}
    
}

