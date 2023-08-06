#ifndef _SQUARE_H_
#define _SQUARE_H_ 
#include <iostream>
#include <cmath>

#include "oscillator.h"

#pragma once


class Square : public Oscillator
{
public:
  //Constructor and destructor
  Square(float frequency, float amplitude, float samplerate = 44100);
  ~Square(); 

  // go to next sample
  void calculate();

}; //

#endif
