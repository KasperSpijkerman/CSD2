#ifndef BLOK2B_Synth_H
#define BLOK2B_Synth_H
#include "oscillator.h"
class Synth 
{
public: 
  Synth();
  float getSample();
  void synthTick();

protected:
  float frequency;
  Oscillator* myOscillators[3];
  int midinote;
};

#endif 
