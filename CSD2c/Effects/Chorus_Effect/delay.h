#pragma once
#include "circBuffer.h"
#include "interpolated_circBuffer.h"

class Delay : public Effect 
{
public:
	Delay();
	~Delay();

	float output(float input);
	void prepareToPlay(double samplerate);
	void bypass (bool bypass);
	// function for converting miliseconds to samples 
	int msToSamp(float ms, double samplerate);

	// setters
	void setDelayTime(float delayTime);
    void setMaxDelay(float maxDelay)
	void setFeedback(float feedback);

private:
	Interpolated_CircBuffer* delayBuffer;
	float delayTimeMs { 0 };
	int delaySamples { 0 };
	float outputDelay { 0 };
	float delayFeedback { 0 };
};