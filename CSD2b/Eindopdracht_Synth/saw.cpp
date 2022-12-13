//
// Created by Ciska Vriezenga on 06/12/2022.
//

#include "saw.h"
#include "math.h"

Saw::Saw(float frequency,float amplitude) : Oscillator(frequency,amplitude)
{
  std::cout << "Saw::Saw constructor\n";
}

void Saw::calculate() 
{
  sample = (2*amplitude * phase) - amplitude;
}