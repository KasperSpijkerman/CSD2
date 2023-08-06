#include "delay.h"


Delay::Delay() 
{
	delayBuffer = new CircBuffer(44100 * 20);
}
Delay::~Delay() 
{
    delete delayBuffer;
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