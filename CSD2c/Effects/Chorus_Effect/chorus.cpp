#include "chorus.h"

Chorus::Chorus()
{
}
Chorus::~Chorus()
{
}

void Chorus::prepareToPlay(double sampleRate)
{
        delay.prepareToPlay(sampleRate);
        delay.setDelayTime(delayTime);
        oscillator.setSamplerate(sampleRate);
}


void Chorus::tick(uint channel)
{
    oscillator[channel].tick();
    float modulation = delayTime + depth * oscillator[channel].getSample();
    delay[channel].setDelayTime(modulation);
}

float Chorus::output(float input)
{
    tick(channel);
    return input * dry + delays[channel].output(input) * wet;
}

float Chorus::calculateDelay()
{

}