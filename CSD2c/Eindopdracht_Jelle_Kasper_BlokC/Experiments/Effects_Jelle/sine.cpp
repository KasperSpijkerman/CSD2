#include "sine.h"
#include "math.h"
#include "oscillator.h"

Sine::Sine(float frequency, float amplitude, float samplerate) : Oscillator(frequency, amplitude, samplerate) //constructor
{
  // std::cout << "Sine - constructor\n";
}



Sine::~Sine() { //deconstructor 
  // std::cout << "Sine - destructor\n"; 
}

void Sine::calculate() {
  sample = sin(pi * 2 * phase) * amplitude;
}
