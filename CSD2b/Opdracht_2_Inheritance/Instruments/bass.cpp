//putting the information in the class
#include <iostream>
#include "bass.h"

Bass::Bass(std::string name, float freq) : Instruments(name,freq)
{
std::cout  << "Constructor from the: " << name <<"\n" << freq << "\n";
}


Bass::~Bass()
{
std::cout  << "Destructor from the: " << name <<"\n";
}



void Bass::slide()
{
  std::cout << name << " Does voooom!\n ";
}


