#include "vibe_synth.h"
#include "math.h"
#include <iostream>

Vibe_Synth::Vibe_Synth(int midinote)
{
  std::cout << "Vibe_Synth::Vibe_Synth constructor\n";
  createOscillator();
  frequency = mtof(midinote,0);
  myOscillators[0] -> setFrequency(frequency);
  frequency = mtof(midinote,3);
  myOscillators[1] -> setFrequency(frequency);
  frequency = mtof(midinote,10);
  myOscillators[2] -> setFrequency(frequency);
};


void Vibe_Synth::createOscillator()
{
  myOscillators[0] = new Saw(440,44100,0.5f);
  myOscillators[1] = new Saw(440,44100,0.5f);
  myOscillators[2] = new Square(440,44100,0.5f);
  
}

void Vibe_Synth::tick()
{
  myOscillators[0] ->tick();
  myOscillators[1] ->tick();
  myOscillators[2] ->tick();
}

//a function for returning samples from specific oscillators for Vibe synth
float Vibe_Synth::getSample() 
{
  float VibeOscillators = (myOscillators[0] -> getSample() + myOscillators[1] -> getSample() + myOscillators[2] ->getSample())/3;
  return VibeOscillators;
}

float Vibe_Synth::mtof(int midinote, int detune)
{
float frequency = (440*powf(2.0f,(((midinote+detune)-69.0f)/12)))  ;
std::cout<< frequency <<"\n";
return frequency;
}