//putting the information in the class
#include <iostream>
#include "instrument.h"

Instrument::Instrument() : Instrument(440)
{
    std::cout << "Inside Instrument Constructor()\n ";
}
Instrument::Instrument(float freq) :
freq(freq)
{
 std::cout << "Inside Instrument constructor (frequency)\n";
}

Instrument::~Instrument()
{
  std::cout << "Inside Instrument destructor\n";
}

void Instrument::setFreq(float freq)
{
  if(freq > 0 && freq < 22000) 
  {
    this->freq = freq;
  } 
  else {
    std::cout << "The frequency value is incorrect"
    << " please present a value in the interval [0, 22000]\n";
  }
}

float Instrument::getFreq()
{
    return freq;
}

