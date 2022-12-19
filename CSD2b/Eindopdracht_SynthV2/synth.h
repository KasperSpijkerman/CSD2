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
  //
  void synthSelect(std::string synthOptions[], int chosenSynth, Synth* mySynths[]);
  //the synth has 3 oscillators depending on which synth is selected.
  Oscillator* myOscillators[3];
  //the synth base class has a vibe synth (fm) and an additive synth
  Synth* mySynths[2];
  std::string synthOptions[3] = {"add","vibe","both"};
  int synthNumOptions = 3;
  int chosenSynth = 0;


protected:
  float frequency;
  int midinote;
};

#endif 
