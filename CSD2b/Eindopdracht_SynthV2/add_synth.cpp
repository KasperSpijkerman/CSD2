#include "add_synth.h"
#include "math.h"
#include <iostream>

Add_Synth::Add_Synth()
{
  std::cout << "Add_Synth::Add_Synth constructor\n";
  //creating combination of different oscillators for this synth
  createOscillator();
};

//creating oscillators with pointers
void Add_Synth::createOscillator()
{
  myOscillators[0] = new Saw(440,0.5f);
  myOscillators[1] = new Saw(440,0.5f);
  myOscillators[2] = new Square(440,0.5f);
}

float Add_Synth::getSample() 
{
  float Oscillators =(myOscillators[0]-> getSample())+ (myOscillators[1] -> getSample()) + (myOscillators[2] ->getSample()/3);;
  
  return Oscillators;
  
}



