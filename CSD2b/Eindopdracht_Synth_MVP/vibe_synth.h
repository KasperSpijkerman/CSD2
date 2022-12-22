#ifndef BLOK2B_Vibe_Synth_H
#define BLOK2B_Vibe_Synth_H
#include "synth.h"
#include "sine.h"

class Vibe_Synth : public Synth
{
public: 
  Vibe_Synth();
  // void setSamplerate();
  void createOscillator();
  float getSample();
  //function for setting amplitude speed
  void setampFrequency(float frequency);
public:
  float ampMod;
  Sine ampsine =  Sine(2,1);
  double amIndex = 3;
};

#endif 
