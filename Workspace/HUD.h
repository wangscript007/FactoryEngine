
#pragma once

#include <Model/Node.h>

namespace ftr {

class HUD : public Node
{
public:    
    void Render(Layer& layer);
    void RenderDesktop(Layer& layer);
    
private:
    RectanglePrimitive rectanglePrimitive[6];
    RectanglePrimitive desktopPrimitive;
};

}
