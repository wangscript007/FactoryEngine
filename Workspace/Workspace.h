// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

#include <Model/Node.h>
#include <Math/Rect.h>
#include <Workspace/Pad.h>
#include <Workspace/HUD.h>
#include <Render/Layer.h>

namespace ftr {

class Workspace : public Node
{
public:
    Workspace();
    ~Workspace();
    virtual void Render(Layer& layer);
    void setViewportRect(Rect rect);
    
private:
    Pad* mPad;
    HUD* mHUD;
};

}
