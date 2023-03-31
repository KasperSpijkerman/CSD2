#include "monoChorus.h"
#include "sine.h"
#include "saw.h"
#include "square.h"

MonoChorus::MonoChorus() : Effect(){

}

MonoChorus::~MonoChorus(){
    // delete buffer;
}

void MonoChorus::prepareToPlay(double sampleRate){
    Effect::sampleRate = sampleRate;
    minDelay = 1; //initialise the minimum delay in ms
    modDepth = 5; //initialise the modulation depth range the modulation modulates between
    modRate = 5; //initialise the modulation rate (freq of the LFO)
    maxDelay = minDelay + modDepth; //the maximum delaytime 
    float maxDelaySamples = msToSamples(maxDelay, sampleRate);
    std::cout << "this is the maxDelaySamples: " << maxDelaySamples << std::endl;
    calculateDelayCenter(); //function calculating the center of the delay that is going to be modulated 
    std::cout << "this is the delaycenter ms: " << delayCenterMs << std::endl;
    std::cout << "this is the delaycenter samples: " << delayCenterSamples << std::endl;
    osc = new Sine(modRate,0.99,Effect::sampleRate); //use sine as LFO
    buffer = new CircBuffer(sampleRate); //make buffer as big as the maximum delay time
}

float MonoChorus::output(float input){
    //calculating the delayline in ms
    float newDelayDistMs = calculateDelayLine();
    //transfer ms to samples
    float newDelayDistSamples = msToSamples(newDelayDistMs,sampleRate);
    //set the distance of the buffer in samples
    buffer -> setDistance(newDelayDistSamples);
    //input value in buffer
    buffer -> input(input);
    //return interpolated output
    float outputBuffer = buffer -> interpolatedOutput();
    buffer -> incrementHeads();
    
    return (outputBuffer*wet)+(input*dry);
} 

void MonoChorus::setMaxDelay(int ms){
    maxDelay = ms;
    minDelay = maxDelay - modRate;
    calculateDelayCenter();
}

void MonoChorus::setMinDelay(int ms){
    minDelay = ms;
    maxDelay = minDelay + modRate;
    calculateDelayCenter();
}

void MonoChorus::setModDepth(float depth){
    modDepth = depth;
    // osc -> setAmplitude(modDepth);
}

void MonoChorus::calculateDelayCenter(){
    delayCenterMs = ((maxDelay-minDelay)/2)+minDelay;
    delayCenterSamples = msToSamples(delayCenterMs, sampleRate);
}

float MonoChorus::calculateDelayLine(){
    // -1 tot 1
    float value = osc->tick();
    // 0 tot 1
    value = (value + 1)/2;
    // 0 tot modDepth
    value = value * modDepth;
    // (minDelay) tot (modDepth + minDelay)
    value += minDelay;
    return value;
}

void MonoChorus::setRate(float freq){
    modRate = freq; 
    osc -> setFrequency(freq);
}



