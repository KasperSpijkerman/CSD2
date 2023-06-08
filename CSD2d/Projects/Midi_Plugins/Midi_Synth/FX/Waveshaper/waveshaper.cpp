// based on code from example
#include "waveshaper.h"

WaveShaper::WaveShaper()
{
    buffer = new float[bufferSize];
    memset(buffer, 0, sizeof(buffer));
    setDryWet(1);
}

WaveShaper::~WaveShaper() 
{
    deleteBuffer();
}

void WaveShaper::prepareToPlay(double samplerate) 
{
    // clearing buffer
    memset(buffer, 0, sizeof(buffer));

}

float WaveShaper::output(float input)
{
	float index = (input + 1.0f) * (bufferSize * 0.5f);
    int i = (int) trunc (index);
    float indexDecimal = index - (float) i;
    // returning shaped signal and dry signal 
	return ((util.linearMap (indexDecimal, buffer[i], buffer[i + 1])*wet) + input*dry)*amplitude;
}

void WaveShaper::setDrive(float k)
{
  // fill buffer using arc-tan function
    for (int i = 0; i < bufferSize; ++i) 
	{
        float x = util.mapInRange (i, 0.0f, bufferSize, -1.0f, 1.0f);
        buffer[i] = tanh (k * x) / tanh (k);
	}	
}

void WaveShaper::setAmplitude(float amplitude)
{
    this->amplitude = amplitude;
}

void WaveShaper::updateParameters(const float drive, const float amplitude)
{
    setDrive(drive);
    setAmplitude(amplitude);
}

void WaveShaper::deleteBuffer()
{
    delete[] buffer;
}