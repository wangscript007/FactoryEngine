
#include <Render/BatchBucket.h>
#include <Render/PolygonBatch.h>
#include <Render/LineBatch.h>

namespace ftr {
    
BatchBucket::~BatchBucket()
{
    Clear();
}

void BatchBucket::AddPrimitive(Primitive& primitive)
{
    OptionToBatchMap& map = mBatchesMap[primitive.type()];
    Batch* batch = NULL;
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
        batch = it->second.back();
    }
    
    if (batch) {
        batch->AddPrimitive(primitive);
        
        if (it != map.end()) {
            if (batch->IsFull()) {
                map.erase(it);
                map[batch->mOptions].push_back(batch);
            }
        } else {
            map[batch->mOptions].push_back(batch);
        }
        
    }
    
}
    
void BatchBucket::Clear()
{
    for (auto& ipair : mBatchesMap) {
        OptionToBatchMap& map = ipair.second;
        for (auto& jpair : map) {
            FT_DELETE_VECTOR(jpair.second);
        }
    }
    mBatchesMap.clear();
}
    
}