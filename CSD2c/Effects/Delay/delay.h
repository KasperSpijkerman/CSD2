#include "circBuffer.h"

class Delay : public Effect 
{
public:
	Delay();
	~Delay();

	float output(float input);

	// setters
	void setDistance(uint distance);
private:
	CircBuffer* delayBuffer;

};