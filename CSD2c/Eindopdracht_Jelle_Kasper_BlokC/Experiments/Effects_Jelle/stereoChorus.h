#ifndef _SCHOR_H_
#define _SCHOR_H_
#include <iostream>
#include <array>
#include <vector>
#include "monoChorus.h"

#pragma once

class StereoChorus {

public:
//constructor and destructor
    StereoChorus();
    ~StereoChorus();
    
//functions for multi channel processing
    void multiChPrepareToPlay (double sampleRate, uint inChannels, uint outChannels);
    float multiChOutput (float input, uint channel);

//setters and getters
    void setChannel(int channel, float depth, int rate, int minimumDelay, float wet);

protected:
//use pointer for MonoChorus class
    MonoChorus *monoChorusArrP;

    uint inputChannels;
    uint outputChannels;
};

#endif