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
protected:
};

#endif 
