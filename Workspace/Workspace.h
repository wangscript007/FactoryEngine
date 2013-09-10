// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

#include <Model/Node.h>
#include <Math/Rect.h>
#include <Workspace/Pad.h>
#include <Workspace/HUD.h>
#include <Workspace/Bounds.h>
#include <Workspace/TestRectangle.h>
#include <Render/Layer.h>
#include <Leap/LeapListener.h>



namespace ftr {

class Workspace : public Node
{
public:
    Workspace(Layer* layer);
    ~Workspace();
    virtual void Render(Layer& layer);
    
private:
    Pad* mPad;
    HUD* mHUD;
    Bounds* mBounds;
    TestRectangle* mTestRactangle;
    
    Layer* mHudLayer;
    Layer* mPadLayer;
    Layer* mBoundsLayer;
    Layer* mModelLayer;
    Layer* mTestLayer;
    Leap::Controller leapController;
    LeapListener leapListener;
};

}
