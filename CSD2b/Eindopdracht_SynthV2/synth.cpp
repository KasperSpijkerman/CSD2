#include "synth.h"
#include "melody.h"
// #include "sine.h"
// #include "math.h"
#include "add_synth.h"
#include "vibe_synth.h"
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

 void Synth::synthSelect(std::string synthOptions[], int chosenSynth, Synth* mySynths[])
 {
  if (synthOptions[chosenSynth] == "add" ) 
  {
    mySynths[0] = new Add_Synth;
    mySynths[1] = new Add_Synth;
    std::cout << mySynths[0] << "\n" << mySynths[1] << "\n";

  }
  if (synthOptions[chosenSynth] == "vibe") 
  {
    mySynths[0] = new Vibe_Synth;
    mySynths[1] = new Vibe_Synth;
    std::cout << mySynths[0] << "\n" << mySynths[1] << "\n";

  }
  if (synthOptions[chosenSynth] == "both") 
  {
    mySynths[0] = new Add_Synth;
    mySynths[1] = new Vibe_Synth;
    std::cout << mySynths[0] << "\n" << mySynths[1] << "\n";

  }
 }
 float Synth::getSample()
 {
 }