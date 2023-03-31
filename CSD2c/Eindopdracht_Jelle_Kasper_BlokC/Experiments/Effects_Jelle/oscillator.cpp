#include "oscillator.h"
#include "math.h"

Oscillator::Oscillator(float frequency, float amplitude, float samplerate) : frequency(frequency), //constructor
  amplitude(amplitude), phase(0), sample(0), samplerate(samplerate)
{
  // std::cout << "oscillator - constructor\n";
}

Oscillator::~Oscillator() { //deconstructor 
  // std::cout << "oscillator - destructor\n"; 
}

void Oscillator::setSamplerate(float samplerate) {
  this->samplerate =samplerate;
}

float Oscillator::getSample() {
  return sample;
}


//getters and setters
void Oscillator::setFrequency(float frequency)
{
  // TODO add check to see if parameter is valid
  this->frequency = frequency;
}

float Oscillator::getFrequency()
{
  return frequency;
}

float Oscillator::tick()
{   
  sample = getSample();  
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  phase += frequency / samplerate;
  if(phase > 1.0f) {
    phase -= 1.0f;
  }
  calculate();
  return sample;
}

void Oscillator::setAmplitude(float amp){
  amplitude = amp;
}