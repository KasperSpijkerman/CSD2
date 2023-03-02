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

        // setters
        void setDepth(float depth);
        void setSpeed(float speed);
        void setMaxDelayTime(float maxDelay);
    private:
        // creating 2 delays for stereo chorus
        Delay delays[2] = {Delay(),Delay()};
        // creating to sine oscillators to modulate the delay
        Sine oscillators[2] = { Sine(speed, 0.5f), Sine(speed, 0.5f) };
        // depth for modulation
        float depth { 0 };
        // delay time
        float delayTime { 0 };
        // set maxDelay time for interval of the chorus
        float maxDelayTime{0};
        // speed for modulation
        float speed {0.5};
        // samplerate will be overwritten
        float sampleRateFX;
};


