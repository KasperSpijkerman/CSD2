#include "circBuffer.h"

class Delay : public Effect 
{
public:
	Delay();
	~Delay();

	float output(float input);
	void prepareToPlay(double samplerate);

	// setters
	void setDistance(uint distance);
private:
	CircBuffer* delayBuffer;

};