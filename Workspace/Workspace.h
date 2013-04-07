// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

#include <Model/Node.h>
#include <Math/Rect.h>
#include <Workspace/Pad.h>
#include <Workspace/HUD.h>

namespace Factory {

class Workspace : public Node
{
public:
                        Workspace();
                        ~Workspace();
    virtual void        Render();
    void                SetViewportRect(Rect rect);
    
private:
    Pad*              mpPad;
    HUD*              mpHUD;
};

}
