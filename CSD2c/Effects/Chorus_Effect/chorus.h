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
        float output(float input,uint channel = 0) ;
        // setters
        void setDepth(float depth);
        void setSpeed(float speed);
        // function for ticking sine and calculating the modulation
        void calcMod(uint channel);
    private:
        // depth for modulation determines the minDelay and maxDelay
        float depth { 1.0f  };
        // delaycenter in ms, will be converted
        float delayCenter{ 30 };
        float delayCenter2 { 50 };
        // speeds for modulation
        float speed { 2 };
        float speed2 { 5 };
        // creating delays for stereo chorus
        Delay delays[2] = {Delay(),Delay()};
        // creating sine oscillators to modulate the delay with different speed
        Sine oscillators[2] = {Sine(speed,0.5f),Sine(speed2,0.5f)};

};


