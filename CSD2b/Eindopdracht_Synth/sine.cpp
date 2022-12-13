//
// Created by Ciska Vriezenga on 06/12/2022.
//

#include "sine.h"
#include "math.h"

Sine::Sine(float frequency,float amplitude) : Oscillator(frequency,amplitude)
{
  std::cout << "Sine::Sine constructor" << frequency << "\n";
}

void Sine::calculate() {
  sample = sin(M_PI * 2 * phase) * amplitude;
}