// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

#include <Model/Node.h>

namespace ftr {

typedef enum {
    kModelTypeCube
} ModelType;


class Model : public Node
{
public:
    ModelType                 m_eType;
    
    void setVertex(Vec3* vertexArray);
    virtual NodeType Type() const { return kNone; }
private:
};

}
