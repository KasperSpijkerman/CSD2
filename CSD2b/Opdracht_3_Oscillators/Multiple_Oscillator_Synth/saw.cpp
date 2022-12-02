#include "saw.h"
#include "math.h"

Saw::Saw(float frequency, float samplerate) :Oscillators(frequency,samplerate)
{
  std::cout << "Saw - constructor " << frequency << "\n";
}



Saw::~Saw() {
  std::cout << "Saw - destructor\n";
}

