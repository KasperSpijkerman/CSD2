#include "lcrDelay.h"
//constructor
LcrDelay::LcrDelay()
{
    DelayArrP = new Delay[3];
}

//destructor
LcrDelay::~LcrDelay()
{

}

void LcrDelay::lcrDelayPrepareToPlay(double samplerate)
{
    // Samplerate
    for(uint i = 0; i < 3; i++)
    {
        DelayArrP[i].prepareToPlay(samplerate);
    };

}

float LcrDelay::lcrDelayOutput(float input, uint ch)
{
    // Variables for all the delaylines
    float LorRoutput;
    float cOutput;
    // Calculating all the values ch 0 = L, 1 = R and 2 = C
    LorRoutput = DelayArrP[ch].output(input);
    // Getting the output for the C delayline but not increment it, the increment happens in the main.cpp
    cOutput = onepole.output(DelayArrP[2].outputNoIncrement(input));
    return LorRoutput + cOutput;
}
void LcrDelay::changeDelayLine(const int ch, const float delaytime, const float feedback, const float drywet,const float bpm,const float division, const bool sync)
{
    distChange = true;
    delayTimesLCR[ch] = (int) delaytime;
    DelayArrP[ch].setDelayTime(delaytime,bpm,division,sync);
    feedbackLCR[ch] = 0;
    distChange = false;

    if (distChange == false)
    {
        feedbackLCR[ch] = feedback;
        DelayArrP[ch].setFeedback(feedback);
    }
    drywetLCR[ch] = drywet;
    DelayArrP[ch].setDryWet(drywet);
}

void LcrDelay::lcrIncrementC()
{
    DelayArrP[2].incrementDelay();
}
