#include "flanger.h"

Flanger::Flanger()
{
}
Flanger::~Flanger()
{
}

void Flanger::prepareToPlay(double sampleRate)
{
        delay.prepareToPlay(sampleRate);
        delay.setDelayTime(delayCenter);
        oscillator.setSamplerate(sampleRate);
        oscillator.setFrequency(speed);
        setDryWet(1);
}

float Flanger::output(float input)
{
    oscillator.tick();
    float modulation = delayCenter * (oscillator.getSample()+1)/2;
    //oscillator.setFrequency(modulation*freq);
    delay.setDelayTime(modulation * depth);
    return input * dry + delay.output(input) * wet;
}
