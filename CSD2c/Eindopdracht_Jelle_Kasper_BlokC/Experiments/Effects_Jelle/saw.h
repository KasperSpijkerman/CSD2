#ifndef _SAW_H_
#define _SAW_H_ 
#include <iostream>
#include <cmath>

#include "oscillator.h"

#pragma once


class Saw : public Oscillator
{
public:
  //Constructor and destructor
  Saw(float frequency = 220, float amplitude = 0.5, float samplerate = 44100);
  ~Saw(); 

  // go to next sample
  void calculate();

}; //

#endif
