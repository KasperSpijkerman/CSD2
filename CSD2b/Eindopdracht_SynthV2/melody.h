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
  void setScale(float newScale[NUM_NOTES]);
  void makeMelodyScale(float array[],int rootNote);

  // void playMelody();

public:
  // float scale[NUM_SCALE] = {1,3,5,7,6,8,10,11,12};
  int rootNote = 70;
  float melody_scale[NUM_NOTES] = {0};
  
  int index;
};

