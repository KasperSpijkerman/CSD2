#include "effect.h"


void Effect::setDryWet(float wetInput) 
{
	
	if(wetInput > 1) 
	{
		wetInput = 1;
	} 
	else if(wetInput < 0) 
	{
		wetInput = 0;
	}
	wet = wetInput;
	dry = 1 - wetInput;
}