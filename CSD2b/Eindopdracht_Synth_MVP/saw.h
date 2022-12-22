//
// Created by Ciska Vriezenga on 06/12/2022.
//

#ifndef BLOK2B_Saw_H
#define BLOK2B_Saw_H
#include "oscillator.h"

class Saw : public Oscillator{
public:
  Saw(float frequency= 0, float amplitude = 0);

protected:
  void calculate();
};


#endif 
