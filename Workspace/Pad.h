// 
//  Copyright (c) 2012 Dimension. All rights reserved.
//
#pragma once

#include <Graph/Node.h>

namespace ftr {

class Pad : Node
{
public:
    Pad() : mfA(50.0f), mfScale(1.0f) {};
    void Render(Layer& layer);
    GLfloat mfA;
    GLfloat mfScale;
    
    LinePrimitive linePrimitive[200];
    RectanglePrimitive rectanglePrimitive;
};
    
}

