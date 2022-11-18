//putting the information in the class
#include <iostream>
#include "instrument.h"
#include <string>

Instrument::Instrument()
{
    frequency = 500;
}
void Instrument::printFrequency()
    {
    std::cout << frequency << std::endl;
    }
