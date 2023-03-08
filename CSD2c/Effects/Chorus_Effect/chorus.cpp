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
        delay.setDelayTime(delayCenter);
        oscillator.setSamplerate(sampleRate);
        oscillator.setFrequency(speed);
        setDryWet(0.8);
}

float Chorus::output(float input)
{
    oscillator.tick();
    float modulation = delayCenter + depth * oscillator.getSample();
    delay.setDelayTime(modulation);
    return input * dry + delay.output(input) * wet;
}
