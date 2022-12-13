#include "synth.h"
// #include "sine.h"
// #include "math.h"
#include <iostream>

Synth::Synth()
{
  std::cout << "Synth::Synth constructor\n";
};


float Synth::getSample() 
{
  float Oscillators = (myOscillators[0] -> getSample() + myOscillators[1] -> getSample() + myOscillators[2] ->getSample())/3;
  return Oscillators;
}

void Synth::synthTick()
{
  myOscillators[0] ->tick();
  myOscillators[1] ->tick();
  myOscillators[2] ->tick();
}