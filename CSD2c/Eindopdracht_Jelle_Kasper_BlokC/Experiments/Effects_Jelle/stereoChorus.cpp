#include "StereoChorus.h"

//constructor
StereoChorus::StereoChorus(){

}

//destructor
StereoChorus::~StereoChorus() {
    // delete monoChorusArrP;
}

void StereoChorus::multiChPrepareToPlay(double sampleRate, uint inChannels, uint outChannels){
    outputChannels = outChannels;
    inputChannels = inChannels;
    //make an array with the amount of monochorus according to the number of output channels
    monoChorusArrP = new MonoChorus[outputChannels];
    //initialise the mono chorusses 
    for(uint i = 0; i < outChannels; i++){
        monoChorusArrP[i].prepareToPlay(sampleRate);
    }

    //setting the channels with the variables depth, rate and minimum delay
    setChannel(0,1,8,17,0.8);
    setChannel(1,0.3,15,10,0.8);
}

float StereoChorus::multiChOutput(float input, uint channel){
    float output = monoChorusArrP[channel].output(input);

    return output;
}

void StereoChorus::setChannel(int channel, float depth, int rate, int minimumDelay, float wet){
    // std::cout << "setChannel " << channel << std::endl;
    //monoChorusArrP + 0 = first MonoChorus in the array
   monoChorusArrP[channel].setMinDelay(minimumDelay);
   monoChorusArrP[channel].setRate(rate);
   monoChorusArrP[channel].setModDepth(depth);
   monoChorusArrP[channel].setDryWet(wet);
}


