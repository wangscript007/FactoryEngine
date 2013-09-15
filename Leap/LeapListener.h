//
//  LeapListener.h
//  FactoryEngine
//
//  Created by Edvinas on 9/11/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#pragma once

#include <Leap/Leap.h>
#include <Leap/LeapMath.h>
#include <Interaction/CameraInteraction.h>

namespace ftr {
    
class LeapListener : public Leap::Listener
{
public:
    virtual ~LeapListener() {}
    virtual void onInit(const Leap::Controller&);
    virtual void onConnect(const Leap::Controller&);
    virtual void onDisconnect(const Leap::Controller&);
    virtual void onFrame(const Leap::Controller&);
    
    void setCameraInteraction(CameraInteraction* interaction) { mCameraInteraction = interaction; }

private:

    CameraInteraction* mCameraInteraction;
    Leap::Frame mLastFrame;
};
    
}

