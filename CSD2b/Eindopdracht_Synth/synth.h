#ifndef BLOK2B_Synth_H
#define BLOK2B_Synth_H
#include "oscillator.h"
class Synth
{
public: 
  Synth();
  virtual float getSample() = 0;

protected:
  float frequency;
  Oscillator* myOscillators[3];
  // float attackTime;
  // float decayTime;
  // float sustainLevel;
  // float releaseTime;
};

#endif 
