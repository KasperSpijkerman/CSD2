#pragma once
// Created By Jelle Kraaijveld, We worked together in CSD2C.
#include "delay.h"
#include "onePole.cpp"
#include <iostream>


class LcrDelay {

public:
    // Contructor and destructor
    LcrDelay();
    ~LcrDelay();
    // Functions
    void lcrDelayPrepareToPlay (double sampleRate);
    float lcrDelayOutput (float input, uint ch);
    void lcrIncrementC();
    //setters and getters
    void changeDelayLine(const int ch, const float delaytime, const float feedback,const float drywet);
protected:
    // Pointer for all the delays in the LCR delay
    Delay *DelayArrP;
    OnePole onepole;
    bool distChange{false};
};

