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

        }
        delays[0].setDelayTime(delayCenter);
        delays[1].setDelayTime(delayCenter2);
        for(Sine& oscillator : oscillators)
        {
            oscillator.setSamplerate(sampleRate);

        }
//        oscillators[0].setFrequency(speed);
//        oscillators[1].setFrequency(speed2);
//        oscillators[1].setPhase(180);

        setDryWet(0.7);
}


void Chorus::calcMod(uint channel)
{
    oscillators[channel].tick();
    float modulation = depth * oscillators[channel].getSample();
    delays[channel].setDelayTime(delayCenter+modulation);
}

float Chorus::output(float input, uint channel)
{
    calcMod(channel);
    return input * dry + delays[channel].output(input) * wet;
}
