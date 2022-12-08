#include "synth.h"
#include "math.h"

Synth::Synth()
{
  std::cout << "Synth::Synth constructor\n";
};

void Synth::makeSine(float frequency, float samplerate) 
{
  Sine sine = Sine(440.0f,44100.0F)
};

