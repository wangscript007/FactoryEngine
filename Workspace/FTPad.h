// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//
#pragma once

#include <Model/FTNode.h>

class FTPad : FTNode
{
public:
                FTPad() : mfA(16.0f), mfScale(1.0f) {};
    void        Render();
    GLfloat     mfA;
    GLfloat     mfScale;
};

