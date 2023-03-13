#pragma once
#include "circBuffer.h"

class Delay : public Effect 
{
public:
	Delay();
	~Delay();

	float output(float input);
	void prepareToPlay(double samplerate) override;
	void bypass (bool bypass);
	// function for converting miliseconds to samples 
	int msToSamp(float ms, double samplerate);

	// setters
	void setDelayTime(float delayTime);
	void setFeedback(float feedback);

private:
	CircBuffer* delayBuffer;
	float delayTimeMs { 0 };
	int delaySamples { 0 };
	float outputDelay { 0 };
	float delayFeedback { 0.5 };
};