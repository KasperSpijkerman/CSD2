//
// Created by Ciska Vriezenga on 06/12/2022.
//

#include "saw.h"
#include "math.h"

Saw::Saw(float frequency,float amplitude) : Oscillator(frequency,amplitude)
{
  #if DEBUG 
  std::cout << "Saw::Saw constructor\n";
  #endif 
}

void Saw::calculate() 
{
  sample = (2*amplitude * phase) - amplitude;
}