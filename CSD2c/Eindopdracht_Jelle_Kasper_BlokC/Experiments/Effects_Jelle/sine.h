#ifndef _SINE_H_
#define _SINE_H_ 
#include <iostream>
#include <cmath>

#include "oscillator.h"

#pragma once


class Sine : public Oscillator
{
public:
  //Constructor and destructor
  Sine(float frequency = 440, float amplitude = 0.5, float samplerate = 44100);
  ~Sine(); 

  // go to next sample
  void calculate();

}; //

#endif
