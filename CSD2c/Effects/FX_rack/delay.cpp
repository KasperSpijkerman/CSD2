#include "delay.h"


Delay::Delay() 
{
	delayBuffer = new CircBuffer(44100 * 20);
}
Delay::~Delay() 
{
    delete delayBuffer;
}

void Delay::prepareToPlay(double samplerate)
{
	
}

float Delay::output(float input)
{
	
    delayBuffer->input(input);
	float output = delayBuffer->output();
	delayBuffer->incrementHeads();

	return output;
}

void Delay::setDistance(uint distance) {
	delayBuffer->setDistance(distance);
}

void Delay::setDryWet(float dryWet) 
{

}

void Delay::bypass (bool bypass) 
{

}