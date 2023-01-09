#include "vibe_synth.h"
#include <iostream>

Vibe_Synth::Vibe_Synth()
{
#if DEBUG
  std::cout << "Vibe_Synth::Vibe_Synth constructor\n";
#endif
  // creating combination of oscillators
  createOscillator();
};

void Vibe_Synth::createOscillator()
{
  myOscillators[0] = new Sine(440, 1.0f);
  myOscillators[1] = new Sine(440, 1.0f);
  // am modulator
  myOscillators[2] = new Sine(440, 1.0f);
  // extra oscillators (not being used-> avoiding Segmentation 11)
  myOscillators[3] = new Sine(440, 0.5f);
  myOscillators[4] = new Sine(440, 0.5f);
  myOscillators[5] = new Sine(440, 0.5f);
}

void Vibe_Synth::setampFrequency(float frequency)
{
  myOscillators[2]->setFrequency(frequency);
}

float Vibe_Synth::getSample()
{
  // 2 oscillators multiplied by the modulator oscillator ->frequency will be set by user for wobble experience.
  float Oscillators = ((myOscillators[0]->getSample() + myOscillators[1]->getSample()) * myOscillators[2]->getSample()) / 2;
  return Oscillators;
}
