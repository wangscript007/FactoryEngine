//
//  LeapListener.cpp
//  FactoryEngine
//
//  Created by Edvinas on 9/11/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#include <Leap/LeapListener.h>

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
    std::cout << "Frame id: " << frame.id()
    << ", timestamp: " << frame.timestamp()
    << ", hands: " << frame.hands().count()
    << ", fingers: " << frame.fingers().count()
    << ", tools: " << frame.tools().count() << std::endl;
}

    
}

