#pragma once

#include <iostream>
#define NUM_NOTES 9

class Melody
{
public:
  Melody();
  ~Melody();
  float getPitch();
  // void playMelody();

protected:
  float melody[NUM_NOTES] = {60, 64, 67, 71, 64, 67, 64, 60, 55};
  //index number for navigating
  int index;
};

