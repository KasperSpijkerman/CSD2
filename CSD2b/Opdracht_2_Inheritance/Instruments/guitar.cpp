//putting the information in the class
#include <iostream>
#include "guitar.h"


Guitar::Guitar(std::string name,float freq, float amp) :Instruments(name, freq, amp)
{
std::cout << "Constructor from the: " << name <<"\n" << "Main frequency gtr is: " << freq << "\n" << "Default Amp gtr is: " << amp << "\n";
}

Guitar::~Guitar()
{
std::cout << "Destructor from the: " << name <<"\n";
}

void Guitar::screech()
{
  std::cout << name << " Does SCEECH!\n ";
}
