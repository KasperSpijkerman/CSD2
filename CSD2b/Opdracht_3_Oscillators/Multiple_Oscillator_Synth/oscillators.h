#pragma once
#include <iostream>
#include <cmath>

class Oscillators
{
public:
  //Constructor and destructor
  Oscillators(float frequency, float samplerate = 44100);
  ~Oscillators();
  void setSamplerate(float samplerate);
  //return the current sample
  float getSample();
  // go to next sample
  void tick();

  //getters and setters
  void setFrequency(float frequency);
  float getFrequency();

protected:
  const float pi = acos (-1);  //atan(1) * 4; <-- vak van Pieter.
  float frequency;
  float amplitude;
  float phase;
  // sample contains the current sample
  float sample;
  float samplerate;
};


