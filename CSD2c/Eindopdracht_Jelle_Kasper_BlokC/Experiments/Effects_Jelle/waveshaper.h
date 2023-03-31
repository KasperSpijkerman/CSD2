//
// Created by Dean on 14/02/2023.
//
#include "interpolation.h"
#include "effect.h"
#include <cmath>

using uint = unsigned int;

class WaveShaper : public Effect {
public:
    WaveShaper();
    ~WaveShaper();
    
    void prepareToPlay(double sampleRate) override;
    float output (float input) override;
    void setDrive (float k);

private:
    uint bufferSize { 0 };
    float* buffer;
};