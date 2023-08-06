#pragma once
#include "effect.h"
#include "sine.h"

class Tremolo : Effect {
public:    
    void prepareToPlay (double sampleRate);
    float output (float input);
    void setAmplitude (float amplitude);
    void setRate (float rate);

private:
    Sine osc;
    float amp { 1.0f };
};
