#pragma once

#include <iostream>
#include "timer.h"
#define NUM_NOTES 9

class Melody
{
public:
  Melody();
  ~Melody();
  float getPitch();
  // void playMelody();
  void updatePitch();

protected:
  float melody[NUM_NOTES] = {60, 64, 67, 71, 64, 67, 64, 60, 55};
  //create a timer object
  Timer timer;
  int readPointer;
  bool playing{false};
  //index number for navigating
  int index;
};

