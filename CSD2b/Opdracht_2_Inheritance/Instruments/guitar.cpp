//putting the information in the class
#include <iostream>
#include "guitar.h"


Guitar::Guitar(std::string name,float freq) :Instruments(name, freq)
{
std::cout  << "Constructor from the: " << name <<"\n" << freq << "\n";
}

Guitar::~Guitar()
{
std::cout  << "Destructor from the: " << name <<"\n";
}

void Guitar::screech()
{
  std::cout << name << "Does SCEECH!\n ";
}
