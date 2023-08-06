#pragma once
#include "oscillator.h"

class Saw : public Oscillator
{
public:
  Saw(float frequency = 0, float amplitude = 0);

protected:
  void calculate();
};
