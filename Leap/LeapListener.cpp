//
//  LeapListener.cpp
//  FactoryEngine
//
//  Created by Edvinas on 9/11/13.
//  Copyright (c) 2013 Dimension. All rights reserved.
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
     glm::vec3 translation =  glm::vec3(leapTranslation.x, leapTranslation.y, leapTranslation.z);
    Leap::Vector leapRotation = frame.translation(mLastFrame);
     glm::vec3 rotation =  glm::vec3(leapRotation.x, leapRotation.y, leapRotation.z);
    float scale = frame.scaleFactor(mLastFrame);
    if (frame.fingers().count() > 4) {
        if (shouldTranslate) {
            mCameraInteraction->MoveBy(glm::vec2(translation));
        }
        if (shouldRotate && false) {
            mCameraInteraction->RotateBy(glm::vec2(rotation.x, rotation.z));
        }
        if (shouldScale) {
            mCameraInteraction->Zoom(scale);
        }
    }
    mLastFrame = frame;
    return;
#ifdef DEBUG
    std::cout << "Frame id: " << frame.id()
    << ", timestamp: " << frame.timestamp()
    << ", hands: " << frame.hands().count()
    << ", fingers: " << frame.fingers().count()
    << ", tools: " << frame.tools().count()
    << ", translate: " << shouldTranslate << " - " << translation.x << " " << translation.y << " " << translation.z
    << ", rotate: " << shouldRotate
    << ", scale: " << shouldScale << std::endl;
#endif

    


}

    
}

