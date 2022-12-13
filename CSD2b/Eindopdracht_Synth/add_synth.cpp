#include "add_synth.h"
#include "math.h"
#include <iostream>

Add_Synth::Add_Synth(int midinote)
{
  std::cout << "Add_Synth::Add_Synth constructor\n";
  createOscillator();
  frequency = mtof(midinote,0);
  myOscillators[0] -> setFrequency(frequency);
  frequency = mtof(midinote,3);
  myOscillators[1] -> setFrequency(frequency);
  frequency = mtof(midinote,10);
  myOscillators[2] -> setFrequency(frequency);
};


void Add_Synth::createOscillator()
{
  myOscillators[0] = new Saw(440,0.5f);
  myOscillators[1] = new Square(440,0.5f);
  myOscillators[2] = new Square(440,0.5f);
  
}


//a function for returning samples from specific oscillators for add synth


float Add_Synth::mtof(int midinote, int detune)
{
float frequency = (440*powf(2.0f,(((midinote+detune)-69.0f)/12)))  ;
std::cout<< frequency <<"\n";
return frequency;
}