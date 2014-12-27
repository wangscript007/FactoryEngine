
#include <Render/PolygonBatch.h>
#include <Render/Primitive.h>
#include <Shading/ShadingInterface.h>

namespace ftr {
 
PolygonBatch::PolygonBatch()
    : mSize(0)
{}

char* PolygonBatch::CreateRenderData(ShadingInterface& shadingInterface)
{
    Triangulate();
    
    mRenderData.vertices.reserve(mSize);
    mRenderData.normals.reserve(mSize);
    mRenderData.colors.reserve(mSize);
    mRenderData.pickingColors.reserve(mSize);
    
    for (auto& poly : mPolygons) {
        if (poly->mSubpolygons.size()) {
            for (auto& subpoly : poly->mSubpolygons) {
                AppendRenderData(*subpoly);
            }
        } else {
            AppendRenderData(*poly);
        }
    }
    return NULL;
}
    
void PolygonBatch::AppendRenderData(const PolygonPrimitive& primitive)
{
    for (int i = 0; i < 3; ++i) {
        mRenderData.vertices.push_back(glm::vec4(primitive.mVec[i], 1.0f));
        mRenderData.colors.push_back(primitive.mColor);
        mRenderData.pickingColors.push_back(primitive.mPickingColor);
//        mRenderData.normals.push_back(primitive.mSubpolygons);
    }
    
}
    
void PolygonBatch::Triangulate()
{
    mSize = 0;
    for (auto &poly : mPolygons) {
        mSize += poly->Triangulate();
    }
}
    
}