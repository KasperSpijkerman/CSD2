//
// Created by Dean on 27/10/2022.
//
#ifndef _EFF_H_
#define _EFF_H_
#pragma once
#include <array>

using uint = unsigned int;

class Effect {
    
public:
  //constructor and destructor
  Effect();
  ~Effect();

  //setters and getters
  void setInputChannels(int amount); //amount of input channels
  void setOutputChannels(int amount); //amount of output channels
  void setDryWet(float wetSig); //set the wet signal with a float 

  //functions for mono signals
  virtual void prepareToPlay (double sampleRate) = 0;
  virtual float output (float input) = 0;

  float msToSamples(float ms, int sampleRate);//function for calculating ms to samples

protected:
  float wet { 0 };
  float dry { 0 }; 
  int sampleRate { 0 }; 
  uint inputChannels { 0 };
  uint outputChannels { 0 };

};

#endif