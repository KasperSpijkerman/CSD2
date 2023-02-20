#include "waveshaper.h"

WaveShaper::WaveShaper() {}

WaveShaper::~WaveShaper() 
{
    delete[] buffer;
}

void WaveShaper::prepareToPlay(double samplerate) 
{
	buffer = new float[bufferSize];
    // standard drive
    setDrive(200.0f);
}
float WaveShaper::output(float input)
{
	float index = (input + 1.0f) * (bufferSize * 0.5f);
    int i = (int) trunc (index);
    float indexDecimal = index - (float) i;
    
	return Util::linearMap (indexDecimal, buffer[i], buffer[i + 1]);
}

void WaveShaper::setDrive(float k)
{
  // fill buffer using arc-tan function
    for (int i = 0; i < bufferSize; ++i) 
	{
        float x = Util::mapInRange (i, 0.0f, bufferSize, -1.0f, 1.0f);
        buffer[i] = tanh (k * x) / tanh (k);
        //formula for different distortion.
        //atan (k * x) / atan (k);
	}	
}

void WaveShaper::setDryWet(float dryWet) 
{

}

void WaveShaper::bypass (bool bypass)
{

}