//
//  LeapListener.cpp
//  FactoryEngine
//
//  Created by Edvinas on 9/11/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#include <Leap/LeapListener.h>

static const float kActionProbablility = 0.40f;

namespace ftr {
    
    
void LeapListener::onInit(const Leap::Controller&)
{
    
}
    
void LeapListener::onConnect(const Leap::Controller&)
{
    
}
    
void LeapListener::onDisconnect(const Leap::Controller&)
{
    
}
    
void LeapListener::onFrame(const Leap::Controller& controller)
{
    const Leap::Frame& frame = controller.frame();
    
    bool shouldTranslate = frame.translationProbability(mLastFrame) > kActionProbablility;
    bool shouldRotate    = frame.rotationProbability(mLastFrame)    > kActionProbablility;
    bool shouldScale     = frame.scaleProbability(mLastFrame)       > kActionProbablility;
    
    Leap::Vector leapTranslation = frame.translation(mLastFrame);
    Vec3 translation = Vec3(leapTranslation.x, leapTranslation.y, leapTranslation.z);
    //mCameraInteraction->MoveBy(Vec2(translation));
    
    
    std::cout << "Frame id: " << frame.id()
    << ", timestamp: " << frame.timestamp()
    << ", hands: " << frame.hands().count()
    << ", fingers: " << frame.fingers().count()
    << ", tools: " << frame.tools().count()
    << ", translate: " << shouldTranslate << " - " << translation.mX << " " << translation.mY << " " << translation.mZ
    << ", rotate: " << shouldRotate
    << ", scale: " << shouldScale << std::endl;
    
    mLastFrame = frame;

}

    
}

