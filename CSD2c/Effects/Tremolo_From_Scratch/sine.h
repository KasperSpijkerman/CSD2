#pragma once
#include "oscillator.h"

class Sine : public Oscillator
{
public:
  Sine(float frequency = 4, float amplitude = 1);

protected:
  void calculate();
};
