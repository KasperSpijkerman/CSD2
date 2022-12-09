#ifndef BLOK2B_Synth_H
#define BLOK2B_Synth_H
#include "sine.h"
#include "saw.h"

class Synth
{
public: 
  Synth();
  
  // virtual void setSamplerate() = 0;
  float getSample();
  float mtof(int midinote);
  void tick();
  // void setSamplerate();

private:
  Sine sine = Sine(300, 44100.0f);
  Sine sine2 = Sine(400, 44100.0f);
  Saw saw = Saw(200,44100.0f);
  // float attackTime;
  // float decayTime;
  // float sustainLevel;
  // float releaseTime;
};

#endif 
