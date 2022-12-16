#ifndef BLOK2B_Vibe_Synth_H
#define BLOK2B_Vibe_Synth_H
#include "synth.h"
#include "sine.h"
#include "saw.h"
#include "square.h"

class Vibe_Synth : public Synth
{
public: 
  Vibe_Synth();
  // void setSamplerate();
  void createOscillator();
  float getSample();
public:
  float ampMod;
  Sine ampsine =  Sine(2,1);
  double fmIndex = 2;
};

#endif 
