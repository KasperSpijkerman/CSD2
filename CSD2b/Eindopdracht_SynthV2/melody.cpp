#include "melody.h"
#include "synth.h"



Melody::Melody()
{
  std::cout << "inside constructor melody\n"; 
  // makeMelodyScale(melody_scale,rootNote);
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
