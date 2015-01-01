
#include <Render/BatchBucket.h>
#include <Render/PolygonBatch.h>
#include <Render/LineBatch.h>

const int kBatchSizeLimit = 300;

namespace ftr {
    
BatchBucket::~BatchBucket()
{
    Clear();
}

void BatchBucket::AddPrimitive(Primitive& primitive)
{
    OptionToBatchMap& map = mBatchesMap[primitive.type()];
    Batch* batch = NULL; ;
    auto it = map.find(primitive.mOptions);
    if (it == map.end()) {
        switch (primitive.type()) {
            case Primitive::kLine: {
                batch = reinterpret_cast<Batch*>(new LineBatch());
            } break;
                
            case Primitive::kPolygon: {
                batch = reinterpret_cast<Batch*>(new PolygonBatch());
            } break;
                
            default: {
                
            } break;
        }
    } else {
        batch = it->second;
    }
    if (batch) {
        batch->AddPrimitive(primitive);
        map[primitive.mOptions] = batch;
    }
    
}
    
void BatchBucket::Clear()
{
    for (auto& ipair : mBatchesMap) {
        OptionToBatchMap& map = ipair.second;
        for (auto& jpair : map) {
            delete jpair.second;
        }
    }
    mBatchesMap.clear();
}
    
}