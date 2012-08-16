// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

class FTPad : FTNode
{
public:
                FTPad() : mfA(16.0f), mfScale(1.0f) {};
    void        Render();
    GLfloat     mfA;
    GLfloat     mfScale;
};

