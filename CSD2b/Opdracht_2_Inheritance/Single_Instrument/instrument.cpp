//putting the information in the class
#include <iostream>
#include "instrument.h"

Instrument::Instrument() : Instrument(440,0,"Guitar")
{
    std::cout << "Inside Instrument Constructor()\n ";
}
Instrument::Instrument(float freq, float amp, std::string name) :
freq(freq), amp(amp), name(name)
{
 std::cout << "Inside Instrument constructor \n";
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

float Instrument::getAmp()
{
    return amp;
}

void Instrument::setAmp(float amp)
{
  if(amp > 0 && amp < 0.9) 
  {
    this->amp = amp;
  } 
  else {
    std::cout << "The amplitude value is incorrect"
    << " please present a value in the interval [0, 0.9]\n";
  }
}

std::string Instrument::getName()
{
    return name;
}

