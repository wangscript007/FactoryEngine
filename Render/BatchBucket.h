

#pragma once

#include <Render/Batch.h>

namespace ftr {
    
class Primitive;
    
class BatchBucket
{
public:
    typedef std::vector<Batch*> BatchVector;
    typedef std::unordered_map<unsigned int, BatchVector> OptionToBatchMap;
    typedef std::unordered_map<int, OptionToBatchMap> TypeToBatchedMap;
    
    BatchBucket() {}
    virtual ~BatchBucket();
    
    void AddPrimitive(Primitive& primitive);
    void Clear();
    
    OptionToBatchMap& BatchesWithType(Primitive::Type type) { return mBatchesMap[type]; }
    
private:
    
    TypeToBatchedMap mBatchesMap;
};
    
}

