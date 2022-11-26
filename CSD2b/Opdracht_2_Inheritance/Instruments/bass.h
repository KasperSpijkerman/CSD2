//header file for description of instrument class
// #pragma once
#include "instruments.h"
#include <iostream>

class Bass : public Instruments 
{
public:
  Bass(std::string name, float freq, float amp);
  ~Bass();

  //methods
  void slide();

};