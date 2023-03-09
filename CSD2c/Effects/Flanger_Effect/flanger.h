#pragma once
#include "effect.h"
#include "delay.h"
#include "sine.h"
#include "triangle.h"

class Flanger : public Effect
{
    public:
        // constructor & deconstructor
        Flanger();
        ~Flanger();

        void prepareToPlay(double sampleRate) override;
        float output(float input) override;
        // setters
        void setDepth(float depth);
        void setSpeed(float speed);
    private:
        // creating delay for Flanger
        Delay delay;
        // creating triangle oscillator to modulate the delay
        Triangle oscillator;
        // depth for modulation determines the minDelay and maxDelay
        float depth { 0.3 };
        // delaycenter
        float delayCenter{ 2 };
        // speed for modulation
        float speed { 2 };
        // samplerate will be overwritten
        float sampleRateFX;
        float freq = 1.0f;
};


