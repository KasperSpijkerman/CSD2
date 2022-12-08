#pragma once
#include <iostream>
#include <cmath>
#include "oscillators.h" 

class Square : public Oscillators
{
public:
  //Constructor and destructor
  Square(float frequency, float samplerate = 44100);
  ~Square();
  void tick();
};


