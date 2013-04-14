
#pragma once

#include <Model/Model.h>

namespace ftr {

class Lights : public Model
{
public:
    static void TurnOn(int index);
    static void TurnOff(int index);
};
    
}

