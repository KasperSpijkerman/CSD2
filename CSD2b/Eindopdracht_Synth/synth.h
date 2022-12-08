#ifndef BLOK2B_Synth_H
#define BLOK2B_Synth_H

#include "sine.h"

class Synth 
{
public: 
  Synth();
  //make sine
  void makeSine(float frequency, float samplerate);
  virtual void getSample() = 0;
  virtual void setSamplerate() = 0;
};

#endif 
