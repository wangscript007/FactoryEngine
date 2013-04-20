
#pragma once

#include <Model/Node.h>

namespace ftr {

class Lights : public Node
{
public:
    static void TurnOn(int index);
    static void TurnOff(int index);
};
    
}

