#include "melody.h"
#include "synth.h"



Melody::Melody()
{
  std::cout << "inside constructor melody\n"; 
}

Melody::~Melody()
{}


float Melody::getPitch(float melody[])
{
  // wrap index
  if(index >= NUM_NOTES) {
    index = 0;
  }
  // index++ --> first use current value to read from array, after this
  // increment with 1
  return melody[index++];
}

void Melody::setScale(float newScale[NUM_NOTES])
{
  for (int i = 0; i < NUM_NOTES; i++) {
    melody_scale[i] = newScale[i] + rootNote;
  }
}
//function for choosing the scale based on ui.
void Melody::chooseScale(std::string scaleOptions[], int scale, Melody& melody)
{
if (scaleOptions[scale] == "harmonicminor" )
    {
      melody.setScale(harmonicminor);
    }
    if (scaleOptions[scale] == "major" )
    {
      melody.setScale(major);
    }
    if (scaleOptions[scale] == "minor" )
    {
      melody.setScale(minor);
    }
    if (scaleOptions[scale] == "dorian" )
    {
      melody.setScale(dorian);
    }
    if (scaleOptions[scale] == "phrygian" )
    {
      melody.setScale(phrygian);
    }
    if (scaleOptions[scale] == "lydian" )
    {
      melody.setScale(lydian);
    }
    if (scaleOptions[scale] == "mixolydian" )
    {
      melody.setScale(mixolydian);
    }
    if (scaleOptions[scale] == "locrian" )
    {
      melody.setScale(locrian);
    }
}

int Melody::calculateRootnote(int key, int octave, int octaveMultiplier)
{
  
  int rootNote = 21 + key + (octave*octaveMultiplier);

  return rootNote;
}