
#pragma once

#include <Graph/Node.h>

namespace ftr {

class Pivot : Node
{
public:
    void setPosition(const glm::vec3 position) { mPosition = position; };
    glm::vec3 position() const { return mPosition; }
    
    void Render(Layer& layer);
    
    
private:
    glm::vec3 mPosition;
};
    
}

