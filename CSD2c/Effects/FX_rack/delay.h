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
private:
	CircBuffer* delayBuffer;
	//int size {0};

};