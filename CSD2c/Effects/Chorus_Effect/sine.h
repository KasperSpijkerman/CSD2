#pragma once
#include "oscillator.h"

class Sine : public Oscillator
{
public:
  Sine(float frequency = 300, float amplitude = 0.5);

protected:
  void calculate();
};
