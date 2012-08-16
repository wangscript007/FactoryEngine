// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//


typedef enum {
    kFTModelTypeCube
} FTModelType;

class FTModel : public FTNode
{
public:
    FTModelType                mtype;
    
    void                        SetVertex(FTVec3d* vertexArray);
private:
};

