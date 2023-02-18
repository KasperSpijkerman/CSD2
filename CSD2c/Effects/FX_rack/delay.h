#include "circBuffer.h"

class Delay : public Effect 
{
public:
	Delay();
	~Delay();

	float output(float input);
	void prepareToPlay(double samplerate);
	void bypass (bool bypass);

	// setters
	void setDistance(uint distance);
	void setDryWet(float dryWet);
private:
	CircBuffer* delayBuffer;

};