#include "synth.h"
#include "melody.h"
#include <iostream>


Synth::Synth()
{
  std::cout << "Synth::Synth constructor\n";
};

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

 
 float Synth::getSample()
 {
  return 0;
 }
 void Synth:: setampFrequency(float frequency)
 {

 }