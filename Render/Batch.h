
#pragma once

#include <Render/Primitive.h>

namespace ftr {

class Batch : public Primitive
{
public:
    virtual ~Batch() {}
    virtual void AddPrimitive(Primitive& primitive);
    virtual void Invalidate();
    
    size_t size() const { return mPrimitives.size(); }
    
protected:
    std::vector<Primitive*> mPrimitives;
};
    
}

