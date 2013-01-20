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
    FTModelType                 m_eType;
    
    void                        SetVertex(O5Vec3* vertexArray);
    virtual NodeType Type() const { return kNone; }
private:
};

