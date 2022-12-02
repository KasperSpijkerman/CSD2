#include "sine.h"
#include "math.h"

Sine::Sine(float frequency, float samplerate) : Oscillators(frequency,samplerate)
{
  std::cout << "Sine - constructor " << frequency << "\n";
}



Sine::~Sine() {
  std::cout << "Sine - destructor\n";
}