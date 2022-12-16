#pragma once

#include <iostream>
#define NUM_NOTES 8

class Melody
{
public:
  Melody();
  ~Melody();
  float getPitch(float melody[]);
  //function for setting the scale 
  void setScale(float newScale[NUM_NOTES]);

  // void playMelody();

public:
  //setting default rootnote, will be overwritten by UI
  int rootNote = 60;
  float melody_scale[NUM_NOTES] = {0};
  
  int index;
};

