#ifndef BLOK2B_SQUARE_H
#define BLOK2B_SQUARE_H

#include "oscillator.h"

class Square : public Oscillator {
public:
  Square(float frequency= 0,float amplitude = 0);

protected:
  void calculate();
};

#endif 
