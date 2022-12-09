#include "add_synth.h"
#include "math.h"
#include <iostream>

Add_Synth::Add_Synth(int midinote)
{
  std::cout << "Add_Synth::Add_Synth constructor\n";
  frequency = mtof(midinote);
  saw.setFrequency(frequency);
};

void Add_Synth::tick()
{
  saw.tick();
  // sine2.tick();
  // saw.tick();
}

float Add_Synth::getSample() {
  
  float multipleOscillators =  saw.getSample();
  return multipleOscillators;
}

float Add_Synth::mtof(int midinote)
{
float frequency = 440*powf(2.0f,((midinote-69)/12));
std::cout<< frequency <<"\n";
return frequency;
}