//
// Created by Ciska Vriezenga on 06/12/2022.
//

#include "square.h"
#include "math.h"

Square::Square(float frequency,float amplitude) : Oscillator(frequency,amplitude)
{
  std::cout << "Square::Square constructor\n";
}

void Square::calculate() {
  sample = amplitude;
  if(phase > 0.5) {
    sample *=-1.0f;
  }
}