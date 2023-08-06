#ifndef _OSC_H_
#define _OSC_H_
#include <iostream>
#include <cmath>

#pragma once

class Oscillator
{
public:
  //Constructor and destructor
  Oscillator(float frequency, float amplitude, float samplerate = 44100);
  ~Oscillator();
  
  void setSamplerate(float samplerate);
  //return the current sample
  float getSample();

  //getters and setters
  void setFrequency(float frequency);
  void setAmplitude(float amp);
  float getFrequency();
  float tick();

protected:

  float frequency; //the oscillator needs a frequency
  float amplitude; //the osc needs a amplitude 
  float phase; //
  // sample contains the current sample
  float sample;
  float samplerate;
  const float pi = acos (-1);  //atan(1) * 4; <-- vak van Pieter.
  virtual void calculate() = 0;
};


#endif
