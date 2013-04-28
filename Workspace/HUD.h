
#pragma once

#include <Model/Node.h>

namespace ftr {

class HUD : Node
{
public:
    struct Vec4 {
        float x, y, z, a;
    };
    
    struct Vec3 {
        float x, y, z;
    };
    
    void Render(RenderBundle& renderBundle);
    void RenderDesktop(RenderBundle& renderBundle);
    
private:
    RectanglePrimitive rectanglePrimitive[6];
    RectanglePrimitive desktopPrimitive;
};

}
