#ifndef BLOK2B_Add_Synth_H
#define BLOK2B_Add_Synth_H
#include "synth.h"
#include "sine.h"
#include "saw.h"
#include "square.h"

class Add_Synth : public Synth
{
public: 
  Add_Synth();
  // void setSamplerate();
  void createOscillator();
  float getSample();
protected:
  
  float frequency;
};

#endif 
