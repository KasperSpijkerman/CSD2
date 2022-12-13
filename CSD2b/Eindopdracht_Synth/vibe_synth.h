#ifndef BLOK2B_Vibe_Synth_H
#define BLOK2B_Vibe_Synth_H
#include "synth.h"
#include "sine.h"
#include "saw.h"
#include "square.h"

class Vibe_Synth : public Synth
{
public: 
  Vibe_Synth(int midinote);
  // void setSamplerate();
  float getSample();
  float mtof(int midinote, int detune);
  void tick();
  void createOscillator();
protected:
  
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
