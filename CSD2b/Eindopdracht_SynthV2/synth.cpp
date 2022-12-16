#include "synth.h"
#include "melody.h"
// #include "sine.h"
// #include "math.h"
#include <iostream>

Synth::Synth()
{
  std::cout << "Synth::Synth constructor\n";
};


// float Synth::getSample() 
// {
//   float Oscillators =(myOscillators[0]-> getSample())+ (myOscillators[1] -> getSample()) + (myOscillators[2] ->getSample()/3);;
  
//   return Oscillators;
  
// }

void Synth::synthTick()
{
  myOscillators[0] ->tick();
  myOscillators[1] ->tick();
  myOscillators[2] ->tick();
}

float Synth::mtof(int midinote, int interval)
{
float frequency = (440*powf(2.0f,(((midinote + interval)-69.0f)/12)))  ;
std::cout<< frequency <<"\n";
return frequency;
}