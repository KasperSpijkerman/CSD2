#pragma once
#include <iostream>

class Effect {
public:    
    virtual void prepareToPlay (double sampleRate) = 0;
    virtual float output (float input) = 0;
    void setDryWet(float dryWet);
private: 
    float dryWet { 1.0f };
};