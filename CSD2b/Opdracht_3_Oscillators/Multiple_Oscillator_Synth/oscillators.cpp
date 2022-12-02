#include "oscillators.h"
#include "math.h"

Oscillators::Oscillators(float frequency, float samplerate) : frequency(frequency),
  amplitude(1.0), phase(0), sample(0), samplerate(samplerate)
{
  std::cout << "Oscillators - constructor " << frequency << "\n";
}



Oscillators::~Oscillators() {
  std::cout << "Oscillators - destructor\n";
}

void Oscillators::setSamplerate(float samplerate) {
  this->samplerate =samplerate;
}



float Oscillators::getSample() {
  return sample;
}



//getters and setters
void Oscillators::setFrequency(float frequency)
{
  // TODO add check to see if parameter is valid
  this->frequency = frequency;
}

float Oscillators::getFrequency()
{
  return frequency;
}
