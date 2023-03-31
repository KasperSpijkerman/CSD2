#include "lcrDelay.h"

//constructor
LcrDelay::LcrDelay(){

}

//destructor
LcrDelay::~LcrDelay(){

}

void LcrDelay::lcrDelayPrepareToPlay(double samplerate){
    //make array with 3 delays
    DelayArrP = new Delay[3];   
    //set the coefficient of the onepole filter
    onepole.setCoefficient(0.98);
    //initialise the delays
    for(uint i = 0; i < 3; i++){
        //set all delaylines using the values in the array for each parameter
        setDelayLine(i,delayTimesLCR[i],feedbackLCR[i],drywetLCR[i]);
        DelayArrP[i].prepareToPlay(samplerate);
    };

}

float LcrDelay::lcrDelayOutput(float input, uint ch){
//variables for all the delaylines
    float LorRoutput;
    float cOutput;
//calculating all the values ch 0 = L, 1 = R and 2 = C
    LorRoutput = DelayArrP[ch].output(input);
//getting the output for the C delayline but not increment it, the increment happens in the main.cpp
    cOutput = onepole.output(DelayArrP[2].outputNoIncrement(input));
    return LorRoutput + cOutput;
}

void LcrDelay::setDelayLine(int ch, int delaytime, float feedback, float drywet){
    //in this function you pick a channel (0 = L, 1 = C and 2 = R) and set all the parameters of the delay on this channel
    delayTimesLCR[ch] = delaytime;
    DelayArrP[ch].setDelayTime(delaytime);

    feedbackLCR[ch] = feedback;
    DelayArrP[ch].setFeedback(feedback);

    drywetLCR[ch] = drywet;
    DelayArrP[ch].setDryWet(drywet);
}

void LcrDelay::resetDelayLine(int ch, int delaytime, float feedback, float drywet){
 //in this function you pick a channel (0 = L, 1 = C and 2 = R) and change all the parameters of the delay on this channel
    delayTimesLCR[ch] = delaytime;
    DelayArrP[ch].resetDelayTime(delaytime);

    feedbackLCR[ch] = feedback;
    DelayArrP[ch].setFeedback(feedback);

    drywetLCR[ch] = drywet;
    DelayArrP[ch].setDryWet(drywet);
}

void LcrDelay::lcrIncrementC(){
    //the C delay needs to be incremented outside the output() function because we use the C value for L and also R
    DelayArrP[2].incrementDelay();
}