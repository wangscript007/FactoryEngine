// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

#include "../Model/FTNode.h"
#include "../Math/FTRect.h"
#include "FTPad.h"
#include "FTHUD.h"

class FTWorkspace : public FTNode
{
public:
                        FTWorkspace();
                        ~FTWorkspace();
    virtual void        Render();
    void                SetViewportRect(FTRect rect);
    
private:
    FTPad*              mpPad;
    FTHUD*              mpHUD;
};

