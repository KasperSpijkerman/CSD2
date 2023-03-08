#pragma once
#include "effect.h"
#include "delay.h"
#include "sine.h"

class Chorus : public Effect
{
    public:
        // constructor & deconstructor
        Chorus();
        ~Chorus();

        void prepareToPlay(double sampleRate) override;
        float output(float input) override;
        // setters
        void setDepth(float depth);
        void setSpeed(float speed);
    private:
        // creating delay for chorus
        Delay delay;
        // creating sine oscillator to modulate the delay
        Sine oscillator;
        // depth for modulation determines the minDelay and maxDelay
        float depth { 2 };
        // delaycenter
        float delayCenter{ 20 };
        // speed for modulation
        float speed { 5 };
        // samplerate will be overwritten
        float sampleRateFX;
};


