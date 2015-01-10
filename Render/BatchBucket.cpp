
#include <Render/BatchBucket.h>
#include <Render/PolygonBatch.h>
#include <Render/LineBatch.h>

namespace ftr {
 
BatchBucket::BatchBucket()
    :mBatchCount(0),
    mBatchSizeLimit(200)
{}
    
BatchBucket::~BatchBucket()
{
    Clear();
}

Batch* BatchBucket::AddPrimitive(Primitive& primitive)
{
    OptionToBatchMap& map = mBatchesMap[primitive.type()];
    Batch* batch = NULL;
    auto it = map.find(primitive.mOptions);
    if (it == map.end()) {
        switch (primitive.type()) {
            case Primitive::kLine: {
                batch = reinterpret_cast<Batch*>(new LineBatch());
                batch->mBatchBucket = this;
                mBatchCount++;
            } break;
                
            case Primitive::kPolygon: {
                batch = reinterpret_cast<Batch*>(new PolygonBatch());
                batch->mBatchBucket = this;
                mBatchCount++;
                
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
    return batch;
}
    
void BatchBucket::DeleteBatch(Batch* batch)
{
    assert(batch);
    OptionToBatchMap& map = mBatchesMap[batch->type()];
    BatchBucket::BatchVector& batchVector = map[batch->mOptions];
    auto it = std::find(batchVector.begin(), batchVector.end(), batch);
    if (it != batchVector.end()) {
        batchVector.erase(it);
        mBatchCount--;
    }
    if (!batchVector.size()) {
        map.erase(batch->mOptions);
    }
    FT_DELETE(batch);
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
    mBatchCount = 0;
}
    
#pragma mark - Debug
    
BatchBucket::DebugData BatchBucket::GetDebugData()
{
    DebugData data;
    for(auto &batches : mBatchesMap) {
        for (auto& pair : batches.second) {
            BatchBucket::BatchVector& batchVector = pair.second;
            DebugData::TypeData typeData;
            for (auto& batch : batchVector) {
                typeData.batchesCount++;
                typeData.primitivesCount += batch->size();
                if (batch->IsFull()) {
                    typeData.fullBatchesCount++;
                }
                typeData.mapSize = batches.second.size();
            }
            switch (batches.first) {
                case Primitive::kLine: data.mLinesData = typeData;  break;
                case Primitive::kPolygon: data.mPolygonsData = typeData; break;
                default: assert(false); break;
            }
        }
    }
    return data;
}
    
    
}