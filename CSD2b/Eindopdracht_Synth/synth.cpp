#include "synth.h"
#include "math.h"
#include <iostream>

Synth::Synth()
{
  std::cout << "Synth::Synth constructor\n";
};

float Synth::mtof(int midinote)
{
float frequency = 440*powf(2.0f,((midinote-69)/12));
std::cout<< frequency <<"\n";
return frequency;
}

void Synth::tick()
{
  sine.tick();
  sine2.tick();
  saw.tick();
}

float Synth::getSample() {
  
  float multipleOscillators =  sine.getSample()+sine2.getSample()+saw.getSample()/3;
  return multipleOscillators;
}

