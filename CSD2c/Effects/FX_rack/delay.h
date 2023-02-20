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
	int msToSamp(float ms, double samplerate);

	// setters
	void setDelayTime(float delayTime);
private:
	CircBuffer* delayBuffer;
	float delayTimeMs { 0 };
	int delaySamples { 0 };
	

};