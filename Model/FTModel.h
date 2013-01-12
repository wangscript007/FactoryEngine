// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

#include <Model/FTNode.h>

typedef enum {
    kFTModelTypeCube
} FTModelType;


class FTModel : public FTNode
{
public:
    FTModelType                mtype;
    
    void                        SetVertex(O5Vec3* vertexArray);
private:
};

