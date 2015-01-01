
#pragma once

#include <Render/Batch.h>

class ShadingInterface;

namespace ftr {

class LineBatch : public Batch
{
public:
    Type type() const { return kLine; }
    
    LineBatch() {}
    virtual ~LineBatch() {}
    
private:
    void CreateRenderData(ShadingInterface& shadingInterface);
};

}