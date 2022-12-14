#include "melody.h"
#include "synth.h"



Melody::Melody()
{
std::cout << "inside constructor melody\n"; 
makeMelodyScale(melody,rootNote);
}

Melody::~Melody()
{}

void Melody::makeMelodyScale(float melody[],int rootNote)
{
for (int i = 0; i < NUM_NOTES; i++) {
    melody[i] += rootNote;
  }
}

float Melody::getPitch()
{
  // wrap index
  if(index >= NUM_NOTES) {
    index = 0;
  }
  // index++ --> first use current value to read from array, after this
  // increment with 1
  return melody[index++];
}


  


