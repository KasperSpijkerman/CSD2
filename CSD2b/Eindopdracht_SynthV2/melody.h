#pragma once

#include <iostream>
#define NUM_NOTES 9
#define NUM_SCALE 9

class Melody
{
public:
  Melody();
  ~Melody();
  float getPitch(float melody[]);
  void makeMelodyScale(float array[],int rootNote);

  // void playMelody();

public:
  // float scale[NUM_SCALE] = {1,3,5,7,6,8,10,11,12};
  int rootNote = 70;
  float melody_scale[NUM_NOTES] = {0, 2,3, 5,6, 10, 11, 12,10 };
  float melody2_scale[NUM_NOTES] = {12, 10,11, 12,10,12, 10, 11,12 };
  
  int index;
};

