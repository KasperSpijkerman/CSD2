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
        void tick(uint channel);
        // calculate delay
        float calculateDelay();

        // setters
        void setDepth(float depth);
        void setSpeed(float speed);
    private:
        // creating delay for chorus
        Delay delay;
        // creating sine oscillator to modulate the delay
        Sine oscillator;
        // depth for modulation determines the minDelay and maxDelay
        float depth { 0 };
        // minDelay time for interval of the chorus
        float mindelayTime { 5.0f };
        // delaycenter
        float delayCenter{};
        // speed for modulation
        float speed {0.5};
        // samplerate will be overwritten
        float sampleRateFX;
};


