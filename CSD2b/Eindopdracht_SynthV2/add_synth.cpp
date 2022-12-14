#include "add_synth.h"
#include "math.h"
#include <iostream>

Add_Synth::Add_Synth()
{
  std::cout << "Add_Synth::Add_Synth constructor\n";
  createOscillator();
  // frequency = mtof(midinote,3);
  // myOscillators[1] -> setFrequency(frequency);
  // frequency = mtof(midinote,10);
  // myOscillators[2] -> setFrequency(frequency);
};

//creating oscillators with pointers
void Add_Synth::createOscillator()
{
  myOscillators[0] = new Sine(440,0.5f);
  myOscillators[1] = new Sine(440,0.5f);
  myOscillators[2] = new Sine(440,0.5f);
}



