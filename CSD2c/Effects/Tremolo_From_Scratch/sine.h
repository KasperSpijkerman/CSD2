#pragma once
#include "oscillator.h"

class Sine : public Oscillator
{
public:
  Sine(float frequency = 0, float amplitude = 1);

protected:
  float calculate();
};
