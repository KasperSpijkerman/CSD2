#include "vibe_synth.h"
#include <iostream>

Vibe_Synth::Vibe_Synth() 
{
  std::cout << "Vibe_Synth::Vibe_Synth constructor\n";
  createOscillator();
};


void Vibe_Synth::createOscillator()
{
  myOscillators[0] = new Sine(440,1.0f);
  myOscillators[1] = new Sine(440,1.0f);
  //am modulator
  myOscillators[2] = new Sine(440,1.0f);
  
}

void Vibe_Synth::setampFrequency(float frequency) 
{
myOscillators[2] -> setFrequency(frequency);
}

float Vibe_Synth::getSample() 
{
  //2 oscillators multiplied by the modulator oscillator based with an am index.
  float Oscillators =((myOscillators[0]-> getSample()+ myOscillators[1] -> getSample())*(amIndex *myOscillators[2]->getSample()))/3 ;
  return Oscillators;
  
}

