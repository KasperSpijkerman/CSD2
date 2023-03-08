#pragma once

#include "oscillator.h"

class Square : public Oscillator
{
public:
  Square(float frequency = 0, float amplitude = 0);

protected:
  void calculate();
};

