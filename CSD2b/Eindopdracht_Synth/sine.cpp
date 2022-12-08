#include "sine.h"
#include "math.h"

Sine::Sine(float frequency, float samplerate) : Oscillators(frequency,samplerate)
{
  std::cout << "Sine - constructor " << frequency << "\n";
}



Sine::~Sine() {
  std::cout << "Sine - destructor\n";
}

void Sine::tick() {
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  phase += frequency / samplerate;
  if(phase > 1.0f) {
    phase -= 1.0f;
  }
  sample = sin(pi * 2 * phase) * amplitude;

}