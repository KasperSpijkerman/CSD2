//
// Created by Ciska Vriezenga on 06/12/2022.
//

#include "saw.h"
#include "math.h"

Saw::Saw(float frequency, float samplerate,float amplitude) : Oscillator(frequency, samplerate,amplitude)
{
  std::cout << "Saw::Saw constructor\n";
}

void Saw::calculate() {
  sample = (2*amplitude * phase) - amplitude;
}