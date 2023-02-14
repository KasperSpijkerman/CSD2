#pragma once
#include <cmath>

class Sine {
public:    
    void prepareToPlay (double sampleRate);
    float output();
    float calculate();
    void setDelta (float frequency);
    double getFrequency();
    void resetPhase();

private:
    const float pi = acos (-1.0f);
    float samplerate { 0.0f };
    float phase { 0.0f };
    float currentFrequency { 0.0f };
    float delta { 0.0f };
};
