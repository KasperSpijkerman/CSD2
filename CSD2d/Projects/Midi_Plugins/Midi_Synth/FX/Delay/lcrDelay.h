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
    //variables for the delaylines, 0 = L, 1 = R, 2 = C

    int delayTimesLCR[3]= {2000, 3000, 700};
    float feedbackLCR[3]= {0.1, 0.1, 0.3};
    float drywetLCR[3]= {0,0,0.5};
    // making a boolean to turn the feedback to zero when distance is being changed, avoids crackles in the feedback
};

