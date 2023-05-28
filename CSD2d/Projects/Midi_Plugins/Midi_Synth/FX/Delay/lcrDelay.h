#ifndef _LCRDEL_H_
#define _LCRDEL_H_

#pragma once

#include "delay.h"
#include "onePole.cpp"
#include <iostream>


class LcrDelay {

public:
//concstructor and destructor
    LcrDelay();
    ~LcrDelay();

//functions
    void lcrDelayPrepareToPlay (double sampleRate);
    float lcrDelayOutput (float input, uint ch);
    void lcrIncrementC();

//setters and getters
    void changeDelayLine(const int ch, const float delaytime, const float feedback,const float drywet);
    void setDelayLine(int ch, int delaytime, float feedback, float drywet);
protected:
//pointer for all the delays in the LCR delay
    Delay *DelayArrP;
    OnePole onepole;
//variables for the delaylines, 0 = L, 1 = R, 2 = C

    int delayTimesLCR[3]= {2000, 3000, 700};
    float feedbackLCR[3]= {0.1, 0.1, 0.3};
    float drywetLCR[3]= {0,0,0.5};
    // making a boolean to turn the feedback to zero when distance is being changed, avoids crackles in the feedback
    bool distChange{false};
};

#endif