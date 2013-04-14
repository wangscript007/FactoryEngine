
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
    
    void Render();
    void RenderCube();
    void RenderIcosahedron();
    void RenderDesktop();
};

}
