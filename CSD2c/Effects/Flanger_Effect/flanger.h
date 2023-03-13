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
        float output(float input,uint channel = 0);
        // setters
        void setDepth(float depth);
        void setSpeed(float speed);
        // calculating modulation and ticking oscillators
        void calcMod(uint channel);
    private:
        // creating delays for stereo Flanger
        Delay delays[2] = {Delay(),Delay()};
        // creating triangle oscillator to modulate the delay, different frequency for stereo effect
        Triangle oscillators[2] = {Triangle(0.3,0.7),Triangle(0.7,0.7)};
        // depth for modulation
        float depth { 2.0f };
        // speed for modulation
        float speed { 0.5 };
        // samplerate will be overwritten
        float sampleRateFX;
        float freq {1.0f};
};


