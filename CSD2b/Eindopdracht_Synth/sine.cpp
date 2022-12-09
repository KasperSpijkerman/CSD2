//
// Created by Ciska Vriezenga on 06/12/2022.
//

#include "sine.h"
#include "math.h"

Sine::Sine(float frequency, float samplerate,float amplitude) : Oscillator(frequency, samplerate,amplitude)
{
  std::cout << "Sine::Sine constructor" << frequency << "\n";
}

void Sine::calculate() {
  sample = sin(M_PI * 2 * phase) * amplitude;
}