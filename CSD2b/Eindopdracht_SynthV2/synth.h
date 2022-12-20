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
  //mtof to convert midi to frequency
  float mtof(int midinote, int interval);
  //get sample function, will be overwritten by sub classes
  virtual float getSample();
  virtual void setampFrequency(float frequency);
  //the synth has 3 oscillators depending on which synth is selected.
  Oscillator* myOscillators[3];
protected:
  float frequency;
  int midinote;
};

#endif 
