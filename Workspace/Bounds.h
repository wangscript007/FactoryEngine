
#pragma once

#include <Graph/Node.h>

namespace ftr {
    
class Bounds : Node
{
public:    
    void Render(Layer& layer);
    
private:
    RectanglePrimitive rectanglePrimitive[6];
};
    
}
