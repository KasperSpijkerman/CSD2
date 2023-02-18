#include "effect.h"


void Effect::setDryWet(float dryWet) 
{
	if(dryWet > 1) dryWet = 1;
	else if(dryWet < 0) dryWet = 0;
	this->dryWet = dryWet;
}