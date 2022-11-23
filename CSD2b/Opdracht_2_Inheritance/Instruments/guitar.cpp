//putting the information in the class
#include <iostream>
#include "guitar.h"


Guitar::Guitar(std::string name) :Instruments(name) 
{
std::cout  << "Constructor from the: " << name <<"\n"
}

Guitar::~Guitar()
{
std::cout  << "Constructor from the: " << name <<"\n"
}

void Guitar::screech()
{
  std::cout << name << "Does voooom!\n " << 
}
