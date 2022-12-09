#ifndef BLOK2B_Add_Synth_H
#define BLOK2B_Add_Synth_H
#include "synth.h"
#include "sine.h"
#include "saw.h"

class Add_Synth : public Synth
{
public: 
  Add_Synth(int midinote);
  // void setSamplerate();
  float getSample();
  float mtof(int midinote);
  void tick();

protected:
  Sine sine = Sine(100, 44100.0f,0.4);
  float frequency;
  int midinote;
  // Sine sine2 = Sine(500, 44100.0f,0.4);
  // Saw saw = Saw(200,44100.0f,0.5);
  // float attackTime;
  // float decayTime;
  // float sustainLevel;
  // float releaseTime;
};

#endif 
