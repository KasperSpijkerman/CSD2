//
// Created by Ciska Vriezenga on 06/12/2022.
//

#ifndef BLOK2B_Saw_H
#define BLOK2B_Saw_H
#include "oscillator.h"

class Saw : public Oscillator{
public:
  Saw(float frequency= 0, float samplerate = 44100);

protected:
  void calculate();
};


#endif 
