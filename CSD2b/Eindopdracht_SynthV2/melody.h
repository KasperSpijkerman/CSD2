#pragma once

#include <iostream>
#define NUM_NOTES 9
#define NUM_SCALE 9

class Melody
{
public:
  Melody();
  ~Melody();
  float getPitch();
  // void playMelody();

protected:
  // float scale[NUM_SCALE] = {1,3,5,7,6,8,10,11,12};

  float melody[NUM_NOTES] = {60, 64, 67, 71, 64, 67, 64, 60, 55};
  //  melody[0] = 60 + scale[0];
  //  melody[1] = 60 + scale[1];
  //  melody[2] = 60 + scale[2];
  //  melody[3] = 60 + scale[3];
  //  melody[4] = 60 + scale[4];
  //  melody[5] = 60 + scale[5];
  //  melody[6] = 60 + scale[6];
  //  melody[7] = 60 + scale[7];
  //  melody[8] = 60 + scale[8];
  // //index number for navigating
  int index;
};

