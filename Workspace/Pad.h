// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//
#pragma once

#include <Model/Node.h>

namespace ftr {

class Pad : Node
{
public:
                Pad() : mfA(16.0f), mfScale(1.0f) {};
    void        Render();
    GLfloat     mfA;
    GLfloat     mfScale;
};
    
}

