#ifndef BLOK2B_Synth_H
#define BLOK2B_Synth_H
#include "oscillator.h"
#include "math.h"
class Synth 
{
public: 
  Synth();
  //tick for all the oscillators at the same time
  void synthTick();
  //get sample function, will be overwritten by sub classes
  virtual float getSample();
  virtual void setampFrequency(float frequency);
  //the synth has 6 oscillators depending on which synth is selected.
  double mtof(float mPitch, float interval,float detune);
  Oscillator* myOscillators[6];
protected:
  float frequency;
  int midinote;
};

#endif 
