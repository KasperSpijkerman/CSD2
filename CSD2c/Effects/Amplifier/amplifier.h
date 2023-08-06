#pragma once
#include "effect.h"
#include <iostream>

class Amplifier : public Effect
{
public:    
    void prepareToPlay (double sampleRate);
    float output (float input);
};