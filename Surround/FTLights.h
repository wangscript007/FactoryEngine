
#pragma once

#include "../Model/FTModel.h"

class FTLights : public FTModel
{
public:
    static void TurnOn(int index);
    static void TurnOff(int index);
};

