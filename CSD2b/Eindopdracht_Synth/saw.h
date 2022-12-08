#pragma once
#include <iostream>
#include "oscillators.h"
#include <cmath>

class Saw : public Oscillators
{
public:
  //Constructor and destructor
  Saw(float frequency, float samplerate = 44100);
  ~Saw();
  //Creating saw
  void tick();
};


