#pragma once
#include <iostream>
#include <cmath>
#include "oscillators.h" 

class Sine : public Oscillators
{
public:
  //Constructor and destructor
  Sine(float frequency, float samplerate = 44100);
  ~Sine();
  void tick();
};


