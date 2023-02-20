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
	// setting the effect samplerate equal to given samplerate
	samplerateFX = samplerate;
	// create delaybuffer
	delayBuffer = new CircBuffer(44100*5);
	
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
	// return the input and output based on dry wet 
	return (output*wet) + (input*dry);
}

void Delay::setDelayTime(float delayMs) {
	// setting the variable to input 
	delayTimeMs = delayMs;
	// converting to samples
	delaySamples = msToSamp(delayTimeMs,samplerateFX);
	// using the samples to the distance for the readhead
	delayBuffer->setDistance(delaySamples);
}

void Delay::bypass (bool bypass) 
{

}

int Delay::msToSamp(float ms, double samplerate) 
{
	// amount of samples calculated based on miliseconds and samplerate
	int samples = ms * samplerateFX/1000;
	return samples;
}
