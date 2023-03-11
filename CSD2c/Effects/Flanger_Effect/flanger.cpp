#include "flanger.h"

Flanger::Flanger()
{
}
Flanger::~Flanger()
{
}

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
        setDryWet(0.8);
}

void Flanger::calcMod(uint channel)
{
    oscillators[channel].tick();
    float modulationSignal = (oscillators[channel].getSample() +1) / 2;
    delays[channel].setDelayTime(depth * modulationSignal);
}

float Flanger::output(float input,uint channel)
{
    calcMod(channel);
    return input * dry + delays[channel].output(input) * wet;
}

void Flanger::setDepth(float depth)
{
    this->depth = depth;
}
