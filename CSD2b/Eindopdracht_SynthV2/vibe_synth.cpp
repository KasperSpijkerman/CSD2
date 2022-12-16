#include "vibe_synth.h"
#include <iostream>

Vibe_Synth::Vibe_Synth() 
{
  std::cout << "Vibe_Synth::Vibe_Synth constructor\n";
  createOscillator();
  frequency = mtof(midinote,0);
  myOscillators[0] -> setFrequency(frequency);
  // frequency = mtof(midinote,3);
  // myOscillators[1] -> setFrequency(frequency);
  // frequency = mtof(midinote,10);
  // myOscillators[2] -> setFrequency(frequency);
};


void Vibe_Synth::createOscillator()
{
  myOscillators[0] = new Square(440,0.5f);
  myOscillators[1] = new Sine(440,0.5f);
  myOscillators[2] = new Square(440,0.5f);
  
}

//a function for returning samples from specific oscillators for Vibe synth

