#include "saw.h"
#include "math.h"
#include "oscillator.h"

Saw::Saw(float frequency, float amplitude, float samplerate) : Oscillator(frequency, amplitude, samplerate) //constructor
{
  // std::cout << "Saw - constructor\n";
}



Saw::~Saw() { //deconstructor 
  // std::cout << "Saw - destructor\n"; 
}

void Saw::calculate() {
  sample = (2*amplitude*phase)-amplitude;
}
