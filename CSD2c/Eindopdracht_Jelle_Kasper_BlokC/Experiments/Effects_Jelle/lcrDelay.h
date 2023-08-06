#ifndef _LCRDEL_H_
#define _LCRDEL_H_

#pragma once

#include "delay.h"
#include "onepole.cpp"
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
    void setDelayLine(int ch, int delaytime, float feedback, float drywet);
    void resetDelayLine(int ch, int delaytime,float feedback, float drywet);

protected:
//pointer for all the delays in the LCR delay
    Delay *DelayArrP;
    OnePole onepole;
//variables for the delaylines, 0 = L, 1 = R, 2 = C

    int delayTimesLCR[3]= {700, 400, 300};
    float feedbackLCR[3]= {0.1, 0.1, 0.9};
    float drywetLCR[3]= {0.8,0.8,1.0};
};

#endif