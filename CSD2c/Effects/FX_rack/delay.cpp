#include "delay.h"


Delay::Delay() 
{
}
Delay::~Delay() 
{
    delete delayBuffer;
}

void Delay::prepareToPlay(double samplerate)
{
	// create delaybuffer
	delayBuffer = new CircBuffer(44100 * 3);
	
}

float Delay::output(float input)
{
	// use functions from circBuffer. 
	// giving the input to writehead
    delayBuffer->input(input);
	// reading output and store in variable
	float output = delayBuffer->output();
	// incrementing heads
	delayBuffer->incrementHeads();
	return (output*wet) + (input*dry);
}

void Delay::setDistance(uint distance) {
	delayBuffer->setDistance(distance);
}

void Delay::bypass (bool bypass) 
{

}