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
float Chorus::output(float input)
{

}

void Chorus::tick(uint channel)
{
    oscillators[channel].tick();
    float modulation = delayTime + depth * lfos[channel].getSample();
    delays[channel].setDelayTime(modulation);
}
