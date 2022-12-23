#pragma once
#include "synth.h"
#include "sine.h"

class Vibe_Synth : public Synth
{
public:
  Vibe_Synth();
  // void setSamplerate();
  void createOscillator();
  float getSample();
  // function for setting amplitude speed
  void setampFrequency(float frequency);

public:
  float ampMod;
  // wobble/amplitude index
  double amIndex = 3;
};
