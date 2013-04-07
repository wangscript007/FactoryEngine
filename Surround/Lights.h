
#pragma once

#include <Model/Model.h>

namespace Factory {

class Lights : public Model
{
public:
    static void TurnOn(int index);
    static void TurnOff(int index);
};
    
}

