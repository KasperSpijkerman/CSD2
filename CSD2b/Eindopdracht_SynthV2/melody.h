#pragma once

#include <iostream>
#define NUM_NOTES 8

class Melody
{
public:
  Melody();
  ~Melody();
  float getPitch(float melody[]);
  //function for choosing the scale
  void chooseScale(std::string scaleOptions[], int scale, Melody& melody);
  //function for setting the scale 
  void setScale(float newScale[NUM_NOTES]);

  // void playMelody();

public:
  //setting default rootnote, will be overwritten by UI
  int rootNote = 60;
  float melody_scale[NUM_NOTES] = {0};
  //scales for different melodies
  float harmonicminor[8] = {0,2,3,5,7,8,11,12};
  float minor[8] = {0,2,3,5,7,8,10,12};
  float major[8] = {0,2,4,5,7,9,11,12};
  float dorian[8] = {0,2,3,5,7,9,10,12};
  float phrygian[8] = {0,1,3,5,7,8,10,12};
  float lydian[8] = {0,2,4,6,7,9,11,12};
  float mixolydian[8] = {0,2,4,5,7,9,10,12};
  float locrian[8] = {0,1,3,5,6,8,10,12};
  //list of options of scales
  std::string scaleOptions[8] = {"harmonicminor","minor","major","dorian","phrygian","lydian","mixolydian","locrian"};
  int numOptions = 8;
  
  int index;
};

