#pragma once
#include "effect.h"
#include "delay.h"
#include "sine.h"
#include "triangle.h"

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
        float depth { 4 };
        // delaycenter in ms, will be converted
        float delayCenter{ 4 };
        // speed for modulation
        float speed { 20 };
        // samplerate will be overwritten
        float sampleRateFX;
        float freq = 1.0f;
};


