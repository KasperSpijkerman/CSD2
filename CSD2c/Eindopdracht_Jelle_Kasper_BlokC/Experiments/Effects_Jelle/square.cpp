#include "square.h"
#include "math.h"
#include "oscillator.h"

Square::Square(float frequency, float amplitude, float samplerate) : Oscillator(frequency, amplitude, samplerate) //constructor
{
  // std::cout << "Square - constructor\n";
}



Square::~Square() { //deconstructor 
  // std::cout << "Sine - destructor\n"; 
}

void Square::calculate() {
  if(phase<0.5f){
    sample = amplitude;
  }

  if(phase>0.5f){
    sample = amplitude*-1;
  }
}