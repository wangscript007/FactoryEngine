

#pragma once

#include <Render/Batch.h>

namespace ftr {
    
class Primitive;
    
class BatchBucket
{
public:
    class DebugData
    {
    public:
        struct TypeData{
            int batchesCount;
            int primitivesCount;
            int fullBatchesCount;
            int mapSize;
            TypeData() : batchesCount(0), primitivesCount(0), fullBatchesCount(0), mapSize(0) {}
        };
        
        TypeData mLinesData;
        TypeData mPolygonsData;
    };
    
    typedef std::vector<Batch*> BatchVector;
    typedef std::unordered_map<unsigned int, BatchVector> OptionToBatchMap;
    typedef std::unordered_map<int, OptionToBatchMap> TypeToBatchedMap;
    
    BatchBucket();
    virtual ~BatchBucket();
    
    Batch* AddPrimitive(Primitive& primitive);
    void Clear();
    
    OptionToBatchMap& BatchesWithType(Primitive::Type type) { return mBatchesMap[type]; }
    void DeleteBatch(Batch* batch);
    
    int batchCount() const { return mBatchCount; }
    
    DebugData GetDebugData();
    
private:
    TypeToBatchedMap mBatchesMap;
    int mBatchCount;
    int mBatchSizeLimit;
};
    
}

