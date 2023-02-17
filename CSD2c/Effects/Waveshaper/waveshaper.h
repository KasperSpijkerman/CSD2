#pragma once
#include "utilities.h"
#include "effect.h"
#include <cmath>

using uint = unsigned int;

class WaveShaper : public Effect
{
public:
    WaveShaper ();
    ~WaveShaper();

    float output (float input);
    void setDrive (float k);
    void prepareToPlay(double samplerate);

private:
    uint bufferSize { 512 };
    float* buffer;
};