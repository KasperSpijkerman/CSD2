#pragma once
#include "../utilities.h"
#include "../effect.h"
#include <cmath>

using uint = unsigned int;

class WaveShaper : public Effect
{
public:
    WaveShaper ();
    ~WaveShaper();

    float output (float input);
    void prepareToPlay(double samplerate);
    void deleteBuffer();
    
    // setters 
    void setDrive (float k);
    void setAmplitude(float amplitude);
    // updating parameters
    void updateParameters(const float drive, const float amplitude,const float drywet);
private:
    uint bufferSize { 512 };
    float* buffer;
    Util util;
    float amplitude{1.0f};


};