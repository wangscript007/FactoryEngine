

#include "ColorPickingMapper.h"


namespace ftr {
    
const int B_MASK = 255;
const int G_MASK = 255<<8; //65280
const int R_MASK = 255<<16; //16711680
    
void ColorPickingMapper::MapLevel(GroupNode::Level level)
{
    
}
    
int ColorPickingMapper::IntFromColor(glm::vec3& vec)
{
    int r = vec.x;
    int g = vec.y;
    int b = vec.z;
    return r | (g << 8) | (b << 16);
}
    
glm::vec3 ColorPickingMapper::ColorFromInt(int number)
{
    int r = number & R_MASK;
    int g = number & G_MASK;
    int b = number & B_MASK;
    return glm::vec3(r, g, b);
}
    
}

