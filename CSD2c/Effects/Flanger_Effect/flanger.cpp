#include "flanger.h"

Flanger::Flanger()
{
}
Flanger::~Flanger()
{
}
// prepare to play for delays and oscillators
void Flanger::prepareToPlay(double sampleRate)
{

        for (Delay& delay : delays)
        {
            delay.prepareToPlay(sampleRate);
            delay.setDelayTime(depth);
        }

        for (Triangle& oscillator : oscillators)
        {
            oscillator.setSamplerate(sampleRate);
        }
        // setting dry wet
        setDryWet(0.8);
}

//  ticking the oscillators and calculating modulation for both
void Flanger::calcMod(uint channel)
{
    //ticking both oscillators
    oscillators[channel].tick();
    // calculating mod signal, making it unipolar
    float modulationSignal = (oscillators[channel].getSample() +1) / 2;
    // setting the delay time based on depth.
    delays[channel].setDelayTime(depth * modulationSignal);
}

// giving the input and channel to output function
float Flanger::output(float input,uint channel)
{
    // calculating the mod and giving output based on input and dry wet
    calcMod(channel);
    return input * dry + delays[channel].output(input) * wet;
}
// setting depth
void Flanger::setDepth(float depth)
{
    this->depth = depth;
}
