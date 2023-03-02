#include "chorus.h"

Chorus::Chorus()
{
}
Chorus::~Chorus()
{
}

void Chorus::prepareToPlay(double sampleRate)
{
    for (Delay& delay : delays)
    {
        delay.prepareToPlay(sampleRate);

        delay.setDelayTime(delayTime);
    }
    for (Sine& oscillator : oscillators)
        oscillators.setSamplerate(sampleRate);
}


void Chorus::tick(uint channel)
{
    oscillators[channel].tick();
    float modulation = delayTime + depth * lfos[channel].getSample();
    delays[channel].setDelayTime(modulation);
}

float Chorus::output(float input)
{
    tick(channel);
    return input * dry + delays[channel].output(input) * wet;
}
