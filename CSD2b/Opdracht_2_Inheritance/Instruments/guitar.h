//header file for description of instrument class
// #pragma once
#include <iostream>
#include "instruments.h"

class Guitar : public Instruments 
{
public:
  Guitar(std::string name,float freq);
  ~Guitar();

  //methods
  void screech();
    
};