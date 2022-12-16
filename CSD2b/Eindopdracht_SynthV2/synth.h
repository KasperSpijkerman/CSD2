#ifndef BLOK2B_Synth_H
#define BLOK2B_Synth_H
#include "oscillator.h"
#include "math.h"
class Synth 
{
public: 
  Synth();
  // float getSample();
  void synthTick();
  float mtof(int midinote, int interval);
  Oscillator* myOscillators[3];

protected:
  float frequency;
  int midinote;
};

#endif 
