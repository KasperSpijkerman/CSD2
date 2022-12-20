#include "vibe_synth.h"
#include <iostream>

Vibe_Synth::Vibe_Synth() 
{
  std::cout << "Vibe_Synth::Vibe_Synth constructor\n";
  createOscillator();
  frequency = mtof(midinote,0);
  myOscillators[0] -> setFrequency(frequency);
  
  std::cout << ampMod <<"\n";
};


void Vibe_Synth::createOscillator()
{
  myOscillators[0] = new Sine(440,1.0f);
  myOscillators[1] = new Sine(440,1.0f);
  //fm modulator
  myOscillators[2] = new Sine(440,1.0f);
  
}

float Vibe_Synth::getSample() 
{
  //2 oscillators multiplied by the modulator oscillator based with an fm index
  float Oscillators =((myOscillators[0]-> getSample())+ (myOscillators[1] -> getSample())*(1+fmIndex *myOscillators[2]->getSample()) )/3;
  return Oscillators;
  
}

