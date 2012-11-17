// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

typedef enum {
    kFTModelTypeCube
} FTModelType;


class FTModel : public FTNode
{
public:
    FTModelType                mtype;
    
    void                        SetVertex(FTVec3f* vertexArray);
private:
};

