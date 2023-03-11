#pragma once
#include "circBuffer.h"

class Delay : public Effect 
{
public:
	Delay();
	~Delay();

	float output(float input);
	void prepareToPlay(double samplerate);
	void bypass (bool bypass);
	// function for converting miliseconds to samples 
	float msToSamp(float ms);

	// setters
	void setDelayTime(float delayTime);
	void setFeedback(float feedback);

private:
    CircBuffer delayBuffer{44100*2};
	float delayTimeMs { 0 };
	float delaySamples { 0 };
	float outputDelay { 0 };
	float delayFeedback { 0 };
    int sampleRate;
};