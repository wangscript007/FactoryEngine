
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
    if (primitive.mBatch) return NULL;
    
    if (primitive.type() == Primitive::kPoint) return NULL;
    
    OptionToBatchMap& map = mBatchesMap[primitive.type()];
    Batch* batch = NULL;
    auto it = map.find(primitive.mOptions);
    if (it == map.end()){
        // batch for options not yet exist
        batch = CreateBatch(primitive.type());
        map[primitive.mOptions].push_back(batch);
        batch->AddPrimitive(primitive);
    }
    else {
        // batch for options already exist
        batch = it->second.back();
        if (batch->size() >= mBatchSizeLimit || batch->isZombie() || !batch->isInvalid()) {
            batch = CreateBatch(primitive.type());
            map[primitive.mOptions].push_back(batch);
        }
        batch->AddPrimitive(primitive);
    }
    
    return batch;
}
    
Batch* BatchBucket::CreateBatch(Primitive::Type type)
{
    Batch* batch = NULL;
    switch (type) {
        case Primitive::kLine: {
            batch = reinterpret_cast<Batch*>(new LineBatch());
        } break;
            
        case Primitive::kPolygon: {
            batch = reinterpret_cast<Batch*>(new PolygonBatch());
            
        } break;
            
        default: {} break;
    }
    if (batch) mBatchCount++;
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
    
void BatchBucket::Cleanup()
{
    BatchVector zombiesVector;
    Zombies(zombiesVector);
    for (auto& zombie : zombiesVector) {
        DeleteBatch(zombie);
    }
}
    
void BatchBucket::Zombies(BatchBucket::BatchVector& zombiesVector)
{
    for(auto &batches : mBatchesMap) {
        for (auto& pair : batches.second) {
            BatchBucket::BatchVector& batchVector = pair.second;
            for (auto& batch : batchVector) {
                if (batch->isZombie()) {
                    zombiesVector.push_back(batch);
                }
            }
        }
    }
//    if (zombiesVector.size()) {
//        std::cout << Description();
//    }
}
    
    
#pragma mark - Debug
    
std::string BatchBucket::Description() const
{
    std::stringstream ss;
    bool exist = false;
    for(auto &batches : mBatchesMap) {
        for (auto& pair : batches.second) {
            const BatchBucket::BatchVector& batchVector = pair.second;
            for (auto& batch : batchVector) {
                ss << batch->Description() << "\n";
                exist = true;
            }
        }
    }
    ss << "-------------------\n";
    
    if (exist) {
        return ss.str();
    }
    return "";
}
    
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
    
std::string BatchBucket::DebugData::Description() const
{
    std::stringstream ss;
    return ss.str();
}
    
std::string BatchBucket::DebugData::TypeDataDescription(BatchBucket::DebugData::TypeData typeData) const
{
    std::stringstream ss;
    ss << "batches: ";
    return ss.str();
}

}