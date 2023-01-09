#include "add_synth.h"
#include "math.h"
#include <iostream>

Add_Synth::Add_Synth()
{
#if DEBUG
  std::cout << "Add_Synth::Add_Synth constructor\n";
#endif
  // creating combination of different oscillators for this synth
  createOscillator();
};

// creating oscillators with pointers
void Add_Synth::createOscillator()
{
  myOscillators[0] = new Saw(440, 0.5f);
  myOscillators[1] = new Saw(440, 0.5f);
  myOscillators[2] = new Square(440, 0.5f);
  myOscillators[3] = new Saw(440, 0.5f);
  myOscillators[4] = new Saw(440, 0.5f);
  myOscillators[5] = new Square(440, 0.5f);
}

float Add_Synth::getSample()
{
  float Oscillators = (myOscillators[0]->getSample()) + (myOscillators[1]->getSample()) + (myOscillators[2]->getSample() + myOscillators[3]->getSample() + myOscillators[4]->getSample() + myOscillators[5]->getSample() / 6);
  ;

  return Oscillators;
}
