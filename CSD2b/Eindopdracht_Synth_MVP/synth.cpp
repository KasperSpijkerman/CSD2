#include "synth.h"
#include "melody.h"
#include <iostream>


Synth::Synth()
{
  #if DEBUG 
  std::cout << "Synth::Synth constructor\n";
  #endif
};

//ticking all 6 oscillators at once. 
void Synth::synthTick()
{
  myOscillators[0] ->tick();
  myOscillators[1] ->tick();
  myOscillators[2] ->tick();
  myOscillators[3] ->tick();
  myOscillators[4] ->tick();
  myOscillators[5] ->tick();
}
float Synth::getSample()
{
return 0;
}
void Synth:: setampFrequency(float frequency)
 {

 }
double Synth::mtof(float mPitch, float interval,float detune)
  {
    return (440.0 * pow(2.0, ((mPitch+ interval) - 69.0f)/12.0f))+detune;
  } // mtof()